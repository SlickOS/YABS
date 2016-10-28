#include "../YABS.hpp"
#include "../Util.hpp"

bool YABS::Expand(std::map<std::string, std::string> &variables) {
    for (auto &variable : variables) {
        YABS::Expand(variable.second, variables);
        YABS::ParseFunctions(variable.second);
        Util::Strip(variable.second);
    }
    return true;
}

bool YABS::Expand(std::string &value, std::map<std::string, std::string> &variables) {
    auto location = value.find("$");
    while (location != std::string::npos) {
        auto end = location + 1;
        while (YABS::IsIdentifierChar(value[end]) && end != std::string::npos) {
            end++;
        }
        
        auto varStr = value.substr(location + 1, end - location - 1);

        for (auto &var : variables) {
            if (var.first == varStr) {
                YABS::Expand(var.second, variables);
                value = Util::ReplaceString(value, value.substr(location, end - location), var.second);
                break;
            }
        }

        location = value.find("$", location + 1);
    }
    return true;
}