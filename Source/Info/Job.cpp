#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Job::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        std::cerr << "Project missing name." << std::endl;
        return false;
    }

    if (node["Tasks"]) {
        auto tasks = node["Tasks"];
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            m_Tasks.push_back(it->as<std::string>());
        }
    }

    if (node["Dependencies"]) {
        auto deps = node["Dependencies"];
        for (auto it = deps.begin(); it != deps.end(); it++) {
            m_Dependencies.push_back(it->as<std::string>());
        }
    }

    return true;
}