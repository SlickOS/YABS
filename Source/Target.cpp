#include "Target.hpp"

#include <iostream>
#include "Util.hpp"

bool Target::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        Util::PrintError("Target missing name.", node);
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

    if (node["Commands"]) {
        for (auto sub : node["Commands"]) {
            Command command;
            command.Parse(sub);
            m_Commands.push_back(command);
        }
    }

    if (node["Dependencies"]) {
        for (auto sub : node["Dependencies"]) {
            m_Dependencies.push_back(sub.as<std::string>());
        }
    }

    return true;
}