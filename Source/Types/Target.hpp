#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "Command.hpp"

class Target {
public:
    Target(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Command> &Commands(void) const { return m_Commands; }
    const std::vector<std::string> &Dependencies(void) const { return m_Dependencies; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Variables;
    std::vector<Command> m_Commands;
    std::vector<std::string> m_Dependencies;
};