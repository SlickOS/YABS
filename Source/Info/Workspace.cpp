#include "Info.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

bool Workspace::Parse(const YAML::Node &node) {
    if (node["Tools"]) {
        auto tools = node["Tools"];
        for (auto it = tools.begin(); it != tools.end(); it++) {
            Tool tool;
            tool.Parse(*it);
            m_Tools.push_back(tool);
        }
    }

    if (node["Configurations"]) {
        auto configs = node["Configurations"];
        for (auto it = configs.begin(); it != configs.end(); it++) {
            Configuration config;
            config.Parse(*it);
            m_Configurations.push_back(config);
        }
    }

    if (node["Flags"]) {
        auto flags = node["Flags"];
        for (auto it = flags.begin(); it != flags.end(); it++) {
            auto inner = *it;
            for (auto i = inner.begin(); i != inner.end(); i++) {
                std::string name = i->first.as<std::string>();
                std::string flag = i->second.as<std::string>();
                m_Flags[name] = flag;
            }
        }
    }

    if (node["Projects"]) {
        auto projects = node["Projects"];
        for (auto it = projects.begin(); it != projects.end(); it++) {
            Project project;
            project.Parse(*it);
            m_Projects.push_back(project);
        }
    }

    if (node["Jobs"]) {
        auto jobs = node["Jobs"];
        for (auto it = jobs.begin(); it != jobs.end(); it++) {
            Job job;
            job.Parse(*it);
            m_Jobs.push_back(job);
        }
    }



    // m_Name = node["Name"].as<std::string>();

    // const YAML::Node& nodeArch = node["Architectures"];
    // for (std::size_t i = 0; i < nodeArch.size(); i++) {
    //     const YAML::Node &nodeInner = nodeArch[i];
    //     Architecture arch;
    //     arch.Parse(nodeInner);
    //     m_Architectures.push_back(arch);
    // }

    // const YAML::Node& nodeConfig = node["Configurations"];
    // for (std::size_t i = 0; i < nodeConfig.size(); i++) {
    //     const YAML::Node &nodeInner = nodeConfig[i];
    //     Configuration config;
    //     config.Parse(nodeInner);
    //     m_Configurations.push_back(config);
    // }

    // const YAML::Node& nodeProject = node["Projects"];
    // for (std::size_t i = 0; i < nodeProject.size(); i++) {
    //     const YAML::Node &nodeInner = nodeProject[i];
    //     Project project;
    //     project.Parse(nodeInner);
    //     m_Projects.push_back(project);
    // }

    // const YAML::Node &nodeOutput = node["Output"];
    // m_OutputBinary = nodeOutput["Binaries"].as<std::string>();
    // m_OutputObject = nodeOutput["Objects"].as<std::string>();

    // Flags flags;
    // flags.Parse(node["Flags"]);
    // m_Flags = flags;

    // std::cout << "Architectures: " << std::endl;
    // for (std::size_t i = 0; i < m_Architectures.size(); i++) {
    //     std::cout << "  " << m_Architectures[i] << std::endl;
    // }

    return true;
}