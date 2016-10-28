#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "Task.hpp"

class Tool {
public:
    Tool(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Task> &Tasks(void) const { return m_Tasks; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Variables;
    std::vector<Task> m_Tasks;
};