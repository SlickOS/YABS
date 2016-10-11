#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Configuration::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        std::cerr << "Configuration missing name." << std::endl;
        return false;
    }

    if (node["Flags"]) {
        auto nodePlatform = node["Flags"];
        for (auto it = nodePlatform.begin(); it != nodePlatform.end(); it++) {
            auto inner = *it;
            for (auto i = inner.begin(); i != inner.end(); i++) {
                std::string name = i->first.as<std::string>();
                std::string flag = i->second.as<std::string>();
                m_Flags[name] = flag;
            }
        }
    }
    else {
        std::cerr << "Configuration missing flags." << std::endl;
        return false;
    }

    return true;
}