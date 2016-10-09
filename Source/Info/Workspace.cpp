#include "Info.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

bool Workspace::Parse(const YAML::Node &node) {
    m_Name = node["Name"].as<std::string>();

    const YAML::Node& nodeArch = node["Architectures"];
    for (std::size_t i = 0; i < nodeArch.size(); i++) {
        const YAML::Node &nodeInner = nodeArch[i];
        Architecture arch;
        arch.Parse(nodeInner);
        m_Architectures.push_back(arch);
    }

    const YAML::Node& nodeConfig = node["Configurations"];
    for (std::size_t i = 0; i < nodeConfig.size(); i++) {
        const YAML::Node &nodeInner = nodeConfig[i];
        Configuration config;
        config.Parse(nodeInner);
        m_Configurations.push_back(config);
    }

    const YAML::Node& nodeProject = node["Projects"];
    for (std::size_t i = 0; i < nodeProject.size(); i++) {
        const YAML::Node &nodeInner = nodeProject[i];
        Project project;
        project.Parse(nodeInner);
        m_Projects.push_back(project);
    }

    const YAML::Node &nodeOutput = node["Output"];
    m_OutputBinary = nodeOutput["Binaries"].as<std::string>();
    m_OutputObject = nodeOutput["Objects"].as<std::string>();

    Flags flags;
    flags.Parse(node["Flags"]);
    m_Flags = flags;

    // std::cout << "Architectures: " << std::endl;
    // for (std::size_t i = 0; i < m_Architectures.size(); i++) {
    //     std::cout << "  " << m_Architectures[i] << std::endl;
    // }

    return true;
}