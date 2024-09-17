#include <iostream>
#include <filesystem>

void stage(const std::string& repo, const std::string& file)
{
    // Check if the repo has been created
    std::filesystem::path repoParentPath = repo;
    std::filesystem::path repoPath = repoParentPath / ".bvcs"; 
    if (!std::filesystem::exists(repoPath))
    {
        std::cout << "Initialize " << repo << " repo first" << std::endl;
        return;
    }

    if (!std::filesystem::exists(file))
    {
        std::cout << "File not found" << std::endl;
        return;
    }

    std::filesystem::path stagingPath = repoPath / "staging";
    std::filesystem::path filePath = repoParentPath / file;
}