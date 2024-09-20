#include <iostream>
#include <filesystem>
#include <fstream>
#include <branch.h>
namespace fs = std::filesystem;

void init()
{
    const fs::path bvcsPath{".bvcs"};

    if (fs::exists(bvcsPath))
    {
        std::cout << "Repository already exists in this location" << std::endl;
        return;
    }

    fs::create_directory(bvcsPath);

    fs::create_directory(bvcsPath);
    fs::create_directory(bvcsPath / "objects");
    fs::create_directory(bvcsPath / "staging");
    fs::create_directory(bvcsPath / "refs");
    fs::create_directory(bvcsPath / "refs/heads");

    branch("main");

    std::ofstream headFile(bvcsPath / "HEAD");
    headFile << "ref: refs/heads/main";
    headFile.close();

    std::cout << "Initialized new BVCS repository" << std::endl;
}