#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Project::Parse(const YAML::Node &node) {
    if (node["Name"]) m_Name = node["Name"].as<std::string>();

    if (node["Flags"]) {
        Flags flags;
        flags.Parse(node["Flags"]);
        m_Flags = flags;
    }

    if (node["Files"]) {
        Files files;
        files.Parse(node["Files"]);
        m_Files = files;
    }

    return true;
}