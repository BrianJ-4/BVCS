#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void branch(const std::string& branchName)
{
    // Check if repo has been created
    fs::path repoPath = {".bvcs"}; 
    if (!fs::exists(repoPath))
    {
        std::cout << "Initialize repo first" << std::endl;
        return;
    }

    fs::path newBranchPath = ".bvcs/refs/heads/" + branchName;
    if (fs::exists(newBranchPath))
    {
        std::cout << "Branch already exists" << std::endl;
        return;
    }
    
    std::ofstream newBranch(newBranchPath);
    newBranch.close();
    std::cout << "Created branch " << branchName << std::endl;
}