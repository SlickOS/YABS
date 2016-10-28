#include "Command.hpp"

#include <iostream>

bool Command::Parse(const YAML::Node &node) {
    if (node["Iterate"]) {
        m_Type = std::pair<std::string, std::string>("Iterate", node["Iterate"].as<std::string>());
    }
    else if (node["Tool"]) {
        m_Type = std::pair<std::string, std::string>("Tool", node["Tool"].as<std::string>());
    }
    else if (node["Shell"]) {
        m_Type = std::pair<std::string, std::string>("Shell", node["Shell"].as<std::string>());
    }
    else if (node["Persistence"]) {
        m_Type = std::pair<std::string, std::string>("Persistence", node["Persistence"].as<std::string>());
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

    if (node["Conditions"]) {
        for (auto sub : node["Conditions"]) {
            for (auto condition : sub) {
                std::string name = condition.first.as<std::string>();
                std::string value = condition.second.as<std::string>();
                m_Conditions.push_back(std::pair<std::string, std::string>(name, value));
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

    return true;
}