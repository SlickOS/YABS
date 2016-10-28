#include "../Util.hpp"

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::string Util::GetDirFromFile(const std::string &name) {
    return fs::path(name).parent_path().generic_string();
}