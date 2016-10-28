#include "../Util.hpp"

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