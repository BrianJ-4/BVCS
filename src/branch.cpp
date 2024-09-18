#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;
namespace fs = std::filesystem;

void branch(const string& branchName)
{
    // Check if repo has been created
    fs::path repoPath = {".bvcs"}; 
    if (!fs::exists(repoPath))
    {
        cout << "Initialize repo first" << endl;
        return;
    }

    // Check if branch already exists
    fs::path newBranchPath = ".bvcs/refs/heads/" + branchName;
    if (fs::exists(newBranchPath))
    {
        cout << "Branch already exists" << endl;
        return;
    }
    
    // Create new branch
    ofstream newBranch(newBranchPath);
    newBranch.close();
    cout << "Created branch " << branchName << endl;
}

void deleteBranch(const string& branchName)
{
    // Check if repo has been created
    fs::path repoPath = {".bvcs"}; 
    if (!fs::exists(repoPath))
    {
        cout << "Initialize repo first" << endl;
        return;
    }

    // Check if branch does not exist
    fs::path branchPath = ".bvcs/refs/heads/" + branchName;
    if (!fs::exists(branchPath))
    {
        cout << "Branch does not exist" << endl;
        return;
    }

    // Get the currently checked out branch
    ifstream head(".bvcs/HEAD");
    string line;
    getline(head, line);
    string currentBranch = line.substr(16);
    
    // Check if current branch is the branch we are trying to delete
    if (currentBranch == branchName)
    {
        cout << "Branch is currently checked out" << endl;
        return;
    }
    
    // Delete the branch
    filesystem::remove(branchPath);
    cout << "Deleted branch " << branchName << endl;
}