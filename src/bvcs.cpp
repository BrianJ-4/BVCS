#include <iostream>
#include "bvcs.h"

void printUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\tinit     -i           \tInitialize repository" << std::endl;
    std::cout << "\tstage    -s  <file>   \tStage file" << std::endl;
    std::cout << "\tcommit   -c  <message>\tCommit staged changes along with commit message" << std::endl;
    std::cout << "\tbranch   -b  <name>   \tCreate new branch with name" << std::endl;
    std::cout << "\tcheckout -co <name>   \tCreate new branch with name" << std::endl;
    std::cout << "\thelp     -h           \tDisplay usages" << std::endl;
}

int main(int argc, char const *argv[])
{
    // If less than two arguments then show message on how to use command
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "help" || command == "-h")
    {
        printUsage();
    }
    // bvcs init
    else if (command == "init" || command == "-i")
            init();
    // bvcs stage <file>
    else if (command == "stage" || command == "-s")
    {
        if (argc < 3)
            std::cout << "Usage: bvcs stage <file>" << std::endl;
        else
            stage(argv[2]);
    }
    // bvcs unstage <file>
    else if (command == "unstage" || command == "-u")
    {
        if (argc < 3)
            std::cout << "Usage: bvcs unstage <file>" << std::endl;
        else
            unstage(argv[2]);
    }
    // bvcs commit -m <message>
    else if (command == "commit" || command == "-c")
    {
        if (argc < 4 || argv[2] != "-m")
            std::cout << "Usage: bvcs commit -m <message>" << std::endl;
        else
            commit(argv[3]);
    }
    // bvcs branch
    else if (command == "branch" || command == "-b")
    {
        if (argc < 2)
            std::cout << "Usage: bvcs branch <name>" << std::endl;
        // bvcs branch list
        else if (argc == 3 && std::string(argv[2]) == "list")
            listBranches();
        // bvcs branch <name>
        else if (argc == 3)
            branch(argv[2]);
        // bvcs branch delete <name>
        else if (argc == 4 && std::string(argv[2]) == "delete")
            deleteBranch(argv[3]);
        else
            std::cout << "Usage: bvcs branch <name>" << std::endl;
    }
    // bvcs checkout <branch>
    else if (command == "checkout" || command == "-co")
    {
        if (argc < 3)
            std::cout << "Usage: bvcs checout <branch>" << std::endl;
        else
            checkout(argv[2]);
    }

    else
    {
        std::cout << "Unknown command: use -h to see usages" << std::endl;
    }
    
    return 0;
}