#include "Tool.hpp"

#include <iostream>
#include "../Util.hpp"

bool Tool::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        Util::PrintYAMLError("Tool missing name.", node);
        return false;
    }

    if (node["Variables"]) {
        for (auto sub : node["Variables"]) {
            for (auto var : sub) {
                std::string name = var.first.as<std::string>();
                std::string value = var.second.as<std::string>();
                m_Variables[name] = value;
            }
        }
    }

    if (node["Tasks"]) {
        for (auto sub : node["Tasks"]) {
            Task task;
            task.Parse(sub);
            m_Tasks.push_back(task);
        }
    }

    return true;
}