#pragma once

#include <string>
#include <vector>

namespace Util {
    std::vector<std::string> FindFiles(const std::string &dir, const std::string &ext);
    bool NeedToRebuild(const std::string &obj, const std::string &src);
    bool CheckDirFromFile(const std::string &name);
    bool CheckDir(const std::string &name);
    void CreateDirFromFile(const std::string &file);
    void CreateDir(const std::string &dir);
    void CleanDir(const std::string &dir);
    std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
    std::vector<std::string> Split(const std::string &str, char delim);
}