#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

class Project {
public:
    Project(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Project> &Projects(void) const { return m_Projects; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Variables;
    std::vector<Project> m_Projects;
};