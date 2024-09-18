#ifndef STAGE_H
#define STAGE_H
#include <string>

void stage(const std::string& file);
void unstage(const std::string& file);
void listStagedFiles();

#endif