#include "Task.hpp"

#include <iostream>
#include "Util.hpp"

bool Task::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        Util::PrintError("Task missing name.", node);
        return false;
    }

    if (node["Variables"]) {
        for (auto sub : node["Variables"]) {
            m_Variables.push_back(sub.as<std::string>());
        }
    }

    if (node["Commands"]) {
        for (auto sub : node["Commands"]) {
            Command command;
            command.Parse(sub);
            m_Commands.push_back(command);
        }
    }

    return true;
}