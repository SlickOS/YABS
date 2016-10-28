#include "../YABS.hpp"
#include "../Util.hpp"

#include <iostream>

bool YABS::ParseFunctions(std::string &value) {
    auto location = value.find("+");
    while (location != std::string::npos) {
        auto end = location + 1;
        if (location >= 1 && !YABS::IsIdentifierChar(value[location - 1])) {
            while (YABS::IsFuncIdentifierChar(value[end]) && end != std::string::npos) {
                end++;
            }
            auto funcStr = value.substr(location + 1, end - location - 1);
            if (!funcStr.empty()) {
                auto par = value.find_first_of("()", location);
                auto start = par;
                while (par != std::string::npos) {
                    if (value[par] == '(') {
                        auto str = value.substr(par);
                        YABS::ParseFunctions(str);
                        value = Util::ReplaceString(value, value.substr(par), str);
                    }
                    else if (value[par] == ')') {
                        auto argStr = value.substr(start + 1, par - start - 1);
                        auto args = Util::Split(argStr, ',');
                        for (auto &arg : args) {
                            Util::Strip(arg);
                        }

                        YABS::HandleFunction(funcStr, args);
                        value = Util::ReplaceString(value, value.substr(location, par - location + 1), funcStr);

                        break;
                    }
                    par++;
                }
            }
        }
        location = value.find("+", end);
    }
    return true;
}