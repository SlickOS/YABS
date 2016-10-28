#pragma once

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace Util {
    std::vector<std::string> FindFiles(const std::string &dir, const std::string &ext);
    bool NeedToRebuild(const std::string &obj, const std::string &src);
    bool CheckDirFromFile(const std::string &name);
    bool CheckDir(const std::string &name);
    std::string GetDirFromFile(const std::string &name);
    void CreateDirFromFile(const std::string &file);
    void CreateDir(const std::string &dir);
    void CleanDir(const std::string &dir);
    std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
    void PrintYAMLError(const std::string &message, const YAML::Node &node);
    std::vector<std::string> Split(const std::string &str, char delim);
    std::string &LStrip(std::string &s);
    std::string &RStrip(std::string &s);
    std::string &Strip(std::string &s);
    std::map<std::string, std::string> AppendVariables(const std::map<std::string, std::string> &lhs, const std::map<std::string, std::string> &rhs);
}