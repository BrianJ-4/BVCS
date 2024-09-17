#include <iostream>
#include <filesystem>
#include <fstream>

void init(const std::string& name)
{
    if (std::filesystem::exists(name))
    {
        std::cout << "Repository already exists in this location" << std::endl;
        return;
    }

    std::filesystem::create_directory(name);
    std::filesystem::create_directory(name + "/.bvcs");
    std::filesystem::create_directory(name + "/.bvcs/contents");
    std::filesystem::create_directory(name + "/.bvcs/staging");
    std::filesystem::create_directory(name + "/.bvcs/refs");
    std::filesystem::create_directory(name + "/.bvcs/refs/heads");

    std::ofstream headFile(name + "/.bvcs/HEAD");
    headFile << "ref: refs/heads/main\n";
    headFile.close();

    std::ofstream masterFile(name + "/.bvcs/refs/heads/main");
    masterFile.close();

    std::cout << "Initialized new BVCS repository " << name << std::endl;
}