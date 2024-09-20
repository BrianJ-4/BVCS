#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <branch.h>
namespace fs = std::filesystem;

using namespace std;

string getSystemTime()
{
    // Get the current system date and time
    const auto now = chrono::system_clock::now();
    const time_t t_c = chrono::system_clock::to_time_t(now);
    string time = ctime(&t_c);
    return time;
}

string generateCommitID(const string& message, const string& time)
{
    // Combine the commit message and commit time and remove spaces
    string combined = message + time;
    combined.erase(remove(combined.begin(), combined.end(), ' '), combined.end()); 
    
    // Generate the hash from the combined string
    hash<string> hasher;
    size_t hash = hasher(combined);
    return "c" + std::to_string(hash);
}

string getCommitParent()
{
    // Get currently checked out branch
    string currentBranch = getCheckedOutBranch();    
    fs::path branchPath = ".bvcs/refs/heads/" + currentBranch;
    
    // Find parent commit stored in branch's head 
    string parentCommit;
    ifstream branchHead(branchPath);
    getline(branchHead, parentCommit);
    branchHead.close();
    return parentCommit;
}

void removeDeletedFiles(const fs::path& parentCommitFilesPath, const fs::path& newCommitFilesPath)
{
    // Loop through files directory of parent commit
    for (const auto& dir_entry : fs::recursive_directory_iterator(parentCommitFilesPath))
    {
        // Get path relative to parent commit's file directory and then construct same path relative to working directory 
        fs::path relativePath = dir_entry.path().lexically_relative(parentCommitFilesPath);
        fs::path workingDirFile = fs::current_path() / relativePath;
        
        // If path does not exist then we have deleted the file from working directory, so delete it from
        // new commit's files directory
        if (!fs::exists(workingDirFile))
        {
            fs::path deletedFile = newCommitFilesPath / relativePath;
            fs::remove_all(deletedFile);
        }
    }
}

void commit(const vector<string>& messageVector)
{
    // Check if repo has been created
    fs::path repoPath = ".bvcs"; 
    if (!fs::exists(repoPath))
    {
        cout << "Initialize repo first" << endl;
        return;
    }

    // Check if anything is staged
    fs::path stagingPath = ".bvcs/staging";
    if (fs::is_empty(stagingPath))
    {
        cout << "There are no staged changes" << endl;
        return;
    }

    // Get commit message
    string message;
    for (const auto& word : messageVector)
        message.append(word + " ");
    
    // Generate unique commit ID
    string time = getSystemTime();
    string commitID = generateCommitID(message, time);
    
    // Create directory to store commit contents
    fs::path commitPath = ".bvcs/objects/" + commitID;
    fs::create_directories(commitPath);

    // Create commit metadata file along with its content
    fs::path commitFilePath("data");
    std::ofstream commitFile(commitPath / commitFilePath);
    commitFile << "commit: " << commitID << "\n";
    commitFile << "date: " << time << "\n";
    commitFile << "message: " << message << "\n";
    // Get parent commit to store in commit metadata
    string parentCommit = getCommitParent();
    if (parentCommit != "")
        commitFile << "parent: " << parentCommit; 
    else
    {
        commitFile << "parent: null";
    }
    commitFile.close();

    // Update branch head to point to latest commit
    string currentBranch = getCheckedOutBranch();
    fs::path branchPath = ".bvcs/refs/heads/" + currentBranch;
    ofstream branchHead(branchPath, std::ofstream::trunc);
    branchHead << commitID;
    branchHead.close();

    // Create files directory in new commit
    fs::path newCommitFilesPath = commitPath / "files";
    fs::create_directories(newCommitFilesPath);

    // Copy files directory from parent commit
    // This will ensure that a commit will have a snapshot of the full project at that point in time
    // Fix for Issue #9
    if(parentCommit != "")
    {
        fs::path parentCommitFilesPath = ".bvcs/objects/" + parentCommit + "/files";
        fs::copy(parentCommitFilesPath, newCommitFilesPath, std::filesystem::copy_options::recursive);

        // Remove files that were copied over from previous commit but no longer in working directory
        removeDeletedFiles(parentCommitFilesPath, newCommitFilesPath);
    }

    // Copy over staged files and directories
    for (const auto& dir_entry : fs::recursive_directory_iterator(stagingPath))
    {
        // Get the relative path of the current directory
        fs::path path = dir_entry.path().lexically_relative(stagingPath);
        fs::path targetPath = newCommitFilesPath / path;

        fs::create_directories(targetPath.parent_path());
        fs::copy(dir_entry.path(), targetPath, fs::copy_options::overwrite_existing);
    }

    // Clear the staging directory
    for (const auto& dir_entry : fs::directory_iterator(stagingPath))
        fs::remove_all(dir_entry);
}