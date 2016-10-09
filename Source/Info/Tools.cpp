#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Tools::Parse(const YAML::Node &node) {
    for (std::size_t i = 0; i < node.size(); i++) {
        const YAML::Node &nodeInner = node[i];
        if (nodeInner["Name"] && (nodeInner["Name"].as<std::string>() == "C")) {
            if (nodeInner["Command"]) m_C = nodeInner["Command"].as<std::string>();
        }
        if (nodeInner["Name"] && (nodeInner["Name"].as<std::string>() == "C++")) {
            if (nodeInner["Command"]) m_CXX = nodeInner["Command"].as<std::string>();
        }
        if (nodeInner["Name"] && (nodeInner["Name"].as<std::string>() == "Assembler")) {
            if (nodeInner["Command"]) m_ASM = nodeInner["Command"].as<std::string>();
        }
        if (nodeInner["Name"] && (nodeInner["Name"].as<std::string>() == "Linker")) {
            if (nodeInner["Command"]) m_LD = nodeInner["Command"].as<std::string>();
        }
    }

    return true;
}