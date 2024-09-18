#ifndef COMMIT_H
#define COMMIT_H
#include <vector>
#include <string>

void commit(const std::vector<std::string>& messageVector);
std::string generateCommitID(const std::string& message);

#endif