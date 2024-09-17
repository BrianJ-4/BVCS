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
            std::cout << "Usage: bvcs stage <filename>" << std::endl;
        else
            stage(argv[2]);
    }
    // bvcs commit -m <message>
    else if (command == "commit" || command == "-c")
    {
        if (argc < 4 || argv[2] != "-m")
            std::cout << "Usage: bvcs commit -m <message>" << std::endl;
        else
            commit(argv[3]);
    }
    // bvcs branch <name>
    else if (command == "branch" || command == "-b")
    {
        if (argc < 3)
            std::cout << "Usage: bvcs branch <name>" << std::endl;
        else
            branch(argv[2]);
    }
    // bvcs checout <branch>
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