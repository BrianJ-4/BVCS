#include <iostream>
#include <filesystem>
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

    
}