#include "../YABS.hpp"

bool YABS::IsIdentifierChar(char c) {
    if (std::isalnum(c)) return true;
    if (c == '-' || c == '_') return true;
    if (c == '+' || c == '=') return true;
    return false;
}

bool YABS::IsFuncIdentifierChar(char c) {
    if (std::isalnum(c)) return true;
    if (c == '_') return true;
    return false;
}