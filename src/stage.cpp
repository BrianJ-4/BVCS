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

    // Create the directory where we will store the file and its path
    // Then copy the file, making sure to overwrite in case file has already been staged
    fs::create_directory(stagingFilePath.parent_path());
    fs::copy(filePath, stagingFilePath, fs::copy_options::overwrite_existing);

    cout << "Staged " << file << endl;
}