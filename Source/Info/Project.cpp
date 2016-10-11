#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Project::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        std::cerr << "Project missing name." << std::endl;
        return false;
    }

    if (node["Configurations"]) {
        auto nodeConfig = node["Configurations"];
        for (auto it = nodeConfig.begin(); it != nodeConfig.end(); it++) {
            m_Configurations.push_back(it->as<std::string>());
        }
    }
    else {
        std::cerr << "Project missing configurations." << std::endl;
        return false;
    }

    if (node["Tools"]) {
        auto nodeTools = node["Tools"];
        for (auto it = nodeTools.begin(); it != nodeTools.end(); it++) {
            ProjectTool tool;
            tool.Parse(*it);
            m_Tools.push_back(tool);
        }
    }
    else {
        std::cerr << "Project missing tools." << std::endl;
        return false;
    }

    return true;
}