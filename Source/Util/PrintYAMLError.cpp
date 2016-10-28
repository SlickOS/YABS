#include "../Util.hpp"

#include <iostream>
#include <string>

void Util::PrintYAMLError(const std::string &message, const YAML::Node &node) {
    std::cerr << "Error: " << message << " [Line " << node.Mark().line << ", Column " << node.Mark().column << "]" << std::endl;
}