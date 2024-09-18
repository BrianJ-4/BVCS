#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void stage(const std::string& file)
{
    // Check if repo has been created
    fs::path repoPath = ".bvcs"; 
    if (!fs::exists(repoPath))
    {
        std::cout << "Initialize repo first" << std::endl;
        return;
    }

    // Check if the file exists
    if (!fs::exists(file))
    {
        std::cout << "File not found" << std::endl;
        return;
    }
    
    fs::path filePath(file);                            // Path of file
    fs::path stagingPath = ".bvcs/staging";             // Staging path in repo
    fs::path stagingFilePath = stagingPath / filePath;  // Final path where file should be saved

    // Check if input is a directory or file
    if (fs::is_directory(filePath))
    {
        // If directory, recursively iterate through contents
        for (const auto& dir_entry : fs::recursive_directory_iterator(filePath))
        {
            // Get the relative path of the current directory
            fs::path path = dir_entry.path().lexically_relative(filePath);
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
        std::cout << "Staged " << file << " and its contents" << std::endl;
    }
    else
    {
        // Create the directory where we will store the file and its path
        // Then copy the file, making sure to overwrite in case file has already been staged
        fs::create_directories(stagingFilePath.parent_path());
        fs::copy(filePath, stagingFilePath, fs::copy_options::overwrite_existing);
        cout << "Staged " << file << endl;
    }
}

void unstage(const std::string& file)
{
    // Check if repo has been created
    fs::path repoPath = ".bvcs"; 
    if (!fs::exists(repoPath))
    {
        cout << "Initialize repo first" << endl;
        return;
    }

    fs::path filePath(file);                            // Path of file
    fs::path stagingPath = ".bvcs/staging";             // Staging path in repo
    fs::path stagedFilePath = stagingPath / filePath;  // Final path where file should be saved
    
    // Check if the file exists in staging directory
    if (!fs::exists(stagedFilePath))
    {
        cout << "File not in staging area" << endl;
        return;
    }

    // Check if trying to unstage a directory or file
    // If directory we need to use remove_all to recursively remove
    // Fix for Issue #5
    if (fs::is_directory(stagedFilePath))
    {
        fs::remove_all(stagedFilePath);
        cout << "Unstaged " << file << " and its contents" << endl;
    }
    else
    {
        fs::remove(stagedFilePath);
        cout << "Unstaged " << file << endl;
    }

    // Get the parent of the file we just unstaged
    // Loop while parentPath is empty and we have not reached the root of staging
    // This will clean up any empty parent directories after unstaging a file
    // Fix for Issue #4
    fs::path parentPath = stagedFilePath.parent_path();
    while (fs::is_empty(parentPath) && parentPath != stagingPath)
    {
        fs::remove(parentPath);
        parentPath = parentPath.parent_path();
    }
}

void listStagedFiles()
{
    // Check if repo has been created
    fs::path repoPath = ".bvcs"; 
    if (!fs::exists(repoPath))
    {
        cout << "Initialize repo first" << endl;
        return;
    }

    fs::path stagingPath = ".bvcs/staging";

    if (fs::is_empty(stagingPath))
    {
        cout << "No files staged" << endl;
        return;
    }

    cout << "Staged files and directories:" << endl;
    for (const auto& dir_entry : fs::recursive_directory_iterator(stagingPath))
        cout << dir_entry.path().lexically_relative(stagingPath).string() << endl;
}