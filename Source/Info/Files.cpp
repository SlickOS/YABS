#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Files::Parse(const YAML::Node &node) {
    if (node["Sources"]) {
        for (std::size_t i = 0; i < node["Sources"].size(); i++) {
            const YAML::Node &nodeInner = node["Sources"][i];
            m_Sources.push_back(node["Sources"][i].as<std::string>());
        }
    }
    if (node["Includes"]) {
        for (std::size_t i = 0; i < node["Includes"].size(); i++) {
            const YAML::Node &nodeInner = node["Includes"][i];
            m_Includes.push_back(node["Includes"][i].as<std::string>());
        }
    }
    if (node["Libraries"]) {
        for (std::size_t i = 0; i < node["Libraries"].size(); i++) {
            const YAML::Node &nodeInner = node["Libraries"][i];
            m_Libraries.push_back(node["Libraries"][i].as<std::string>());
        }
    }

    return true;
}