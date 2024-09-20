#ifndef COMMIT_H
#define COMMIT_H
#include <vector>
#include <string>
#include <filesystem>

void commit(const std::vector<std::string>& messageVector);
std::string generateCommitID(const std::string& message, const std::string& time);
std::string getSystemTime();
std::string getCommitParent();
void removeDeletedFiles(const std::filesystem::path& parentCommitFilesPath, const std::filesystem::path& newCommitFilesPath);

#endif