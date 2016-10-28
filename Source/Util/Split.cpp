#include "../Util.hpp"

#include <sstream>
#include <string>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        // if (!item.empty()) elems.push_back(item);
        elems.push_back(item);
    }
}

std::vector<std::string> Util::Split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}