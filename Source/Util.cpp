#include "Util.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::vector<std::string> Util::FindFiles(const std::string &dir, const std::string &ext) {
    fs::recursive_directory_iterator iter(dir);
    std::vector<std::string> files;
    for(auto&& i : iter) {
        if (!fs::is_directory(i) && (i.path().extension() == ("." + ext))) files.push_back(i.path().generic_string());
    }
    return files;
}

bool Util::NeedToRebuild(const std::string &obj, const std::string &src) {
    fs::path objPath(obj);
    fs::path srcPath(src);
    if (!fs::exists(objPath) || !fs::exists(srcPath)) return true;
    return (fs::last_write_time(srcPath) > fs::last_write_time(objPath));
}

bool Util::CheckDirFromFile(const std::string &name) {
    return fs::exists(fs::path(name).parent_path());
}

bool Util::CheckDir(const std::string &name) {
    return fs::exists(fs::path(name));
}

void Util::CreateDirFromFile(const std::string &name) {
    if (Util::CheckDirFromFile(name)) return;
    std::cout << "Making Dir!" << std::endl;
    fs::create_directories(fs::path(name).parent_path());
}

void Util::CreateDir(const std::string &name) {
    if (Util::CheckDir(name)) return;
    fs::create_directories(fs::path(name));
}

std::string Util::ReplaceString(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}