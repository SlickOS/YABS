#include "../Util.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <string>
#include <vector>

std::map<std::string, std::string> Util::AppendVariables(const std::map<std::string, std::string> &lhs, const std::map<std::string, std::string> &rhs) {
    std::map<std::string, std::string> ret = lhs;
    ret = std::accumulate(rhs.begin(), rhs.end(), ret, [](std::map<std::string, std::string> &m, const std::pair<std::string, std::string> &p) {
        return (m[p.first] += " " + p.second, m);
    });
    return ret;
}