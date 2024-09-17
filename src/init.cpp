#include <iostream>
#include <filesystem>
#include <fstream>
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

    std::ofstream headFile(bvcsPath / "HEAD");
    headFile << "ref: refs/heads/main\n";
    headFile.close();

    std::ofstream mainFile(bvcsPath / "refs/heads/main");
    mainFile.close();

    std::cout << "Initialized new BVCS repository" << std::endl;
}