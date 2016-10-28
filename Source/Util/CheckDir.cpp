#include "../Util.hpp"

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool Util::CheckDirFromFile(const std::string &name) {
    return fs::exists(fs::path(name).parent_path());
}

bool Util::CheckDir(const std::string &name) {
    return fs::exists(fs::path(name));
}