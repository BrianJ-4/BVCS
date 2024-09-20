#include <string>
#ifndef BRANCH_H
#define BRANCH_H

void branch(const std::string& branchName);
void deleteBranch(const std::string& branchName);
void listBranches();
std::string getCheckedOutBranch();

#endif