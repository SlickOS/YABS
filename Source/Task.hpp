#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "Command.hpp"

class Task {
public:
    Task(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::vector<std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Command> &Commands(void) const { return m_Commands; }

private:
    std::string m_Name;
    std::vector<std::string> m_Variables;
    std::vector<Command> m_Commands;
};