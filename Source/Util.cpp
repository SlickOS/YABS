#include "Util.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::vector<std::string> Util::FindFiles(const std::string &dir, const std::string &ext) {
    if (!fs::exists(fs::path(dir))) return std::vector<std::string>();
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

void Util::CleanDir(const std::string &name) {
    fs::path dir(name);
    //std::cout << dir.generic_string() << std::endl;
    fs::remove_all(dir);
}

bool Util::CheckDirFromFile(const std::string &name) {
    return fs::exists(fs::path(name).parent_path());
}

bool Util::CheckDir(const std::string &name) {
    return fs::exists(fs::path(name));
}

std::string Util::GetDirFromFile(const std::string &name) {
    return fs::path(name).parent_path().generic_string();
}

void Util::CreateDirFromFile(const std::string &name) {
    if (Util::CheckDirFromFile(name)) return;
    //std::cout << "Making Dir!" << std::endl;
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

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) elems.push_back(item);
    }
}

void Util::PrintError(const std::string &message, const YAML::Node &node) {
    std::cerr << "Error: " << message << " [Line " << node.Mark().line << ", Column " << node.Mark().column << "]" << std::endl;
}

std::vector<std::string> Util::Split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string &Util::LStrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &Util::RStrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &Util::Strip(std::string &s) {
    return LStrip(RStrip(s));
}

std::map<std::string, std::string> Util::AppendVariables(const std::map<std::string, std::string> &lhs, const std::map<std::string, std::string> &rhs) {
    std::map<std::string, std::string> ret = lhs;
    ret = std::accumulate(rhs.begin(), rhs.end(), ret, [](std::map<std::string, std::string> &m, const std::pair<std::string, std::string> &p) {
        return (m[p.first] += " " + p.second, m);
    });
    return ret;
}