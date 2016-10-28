#include "../Util.hpp"

#include <algorithm>
#include <string>

std::string &Util::LStrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string &Util::RStrip(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string &Util::Strip(std::string &s) {
    return LStrip(RStrip(s));
}