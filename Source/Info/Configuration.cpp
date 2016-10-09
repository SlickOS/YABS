#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Configuration::Parse(const YAML::Node &node) {
    if (node["Name"]) m_Name = node["Name"].as<std::string>();

    if (node["Flags"]) {
        Flags flags;
        flags.Parse(node["Flags"]);
        m_Flags = flags;
    }

    return true;
}