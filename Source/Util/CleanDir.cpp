#include "../Util.hpp"

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void Util::CleanDir(const std::string &name) {
    fs::path dir(name);
    fs::remove_all(dir);
}