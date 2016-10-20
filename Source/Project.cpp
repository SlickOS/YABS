#include "Project.hpp"

#include <iostream>
#include "Util.hpp"

bool Project::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        Util::PrintError("Project missing name.", node);
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

    if (node["Projects"]) {
        for (auto sub : node["Projects"]) {
            Project project;
            project.Parse(sub);
            m_Projects.push_back(project);
        }
    }

    return true;
}