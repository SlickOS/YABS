#include "../Util.hpp"

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool Util::NeedToRebuild(const std::string &obj, const std::string &src) {
    fs::path objPath(obj);
    fs::path srcPath(src);
    if (!fs::exists(objPath) || !fs::exists(srcPath)) return true;
    return (fs::last_write_time(srcPath) > fs::last_write_time(objPath));
}