#include "../Util.hpp"

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void Util::CreateDirFromFile(const std::string &name) {
    if (Util::CheckDirFromFile(name)) return;
    fs::create_directories(fs::path(name).parent_path());
}

void Util::CreateDir(const std::string &name) {
    if (Util::CheckDir(name)) return;
    fs::create_directories(fs::path(name));
}