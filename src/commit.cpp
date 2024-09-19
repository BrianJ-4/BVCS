#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
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
    string combined = message + time;
    combined.erase(remove(combined.begin(), combined.end(), ' '), combined.end()); 
    
    hash<string> hasher;
    size_t hash = hasher(combined);
    return "c" + std::to_string(hash);
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

    // Get the commit message
    string message;
    for (const auto& word : messageVector)
        message.append(word + " ");
    
    // Generate a unique commit ID
    string time = getSystemTime();
    string commitID = generateCommitID(message, time);
    
    // Create directory to store commit contents
    fs::path filePath(commitID); 
    fs::path objectsPath = ".bvcs/objects";
    fs::path commitPath = objectsPath / filePath;
    fs::create_directories(objectsPath / commitID);

    // Create commit metadata file along with its content
    fs::path commitFilePath(commitID + ".txt"); 
    std::ofstream commitFile(commitPath / commitFilePath);
    commitFile << "commit: " << commitID << "\n";
    commitFile << "date: " << time << "\n";
    commitFile << "message: " << message << "\n"; 
    commitFile.close();

    // Create directory to store staged files
    fs::create_directories(commitPath / "files");

    // Copy over staged files and directories
    fs::path stagingFilePath = commitPath / "files";
    for (const auto& dir_entry : fs::recursive_directory_iterator(stagingPath))
    {
        // Get the relative path of the current directory
        fs::path path = dir_entry.path().lexically_relative(stagingPath);
        fs::path targetPath = stagingFilePath / path;

        // If directory we create it in staging area
        if (fs::is_directory(dir_entry))
            fs::create_directories(targetPath);
        else
        {
            fs::create_directories(targetPath.parent_path());
            fs::copy(dir_entry.path(), targetPath, fs::copy_options::overwrite_existing);
        }
    }

    // Clear the staging directory
    for (const auto& dir_entry : fs::directory_iterator(stagingPath))
        fs::remove_all(dir_entry);
}