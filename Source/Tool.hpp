#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "Rule.hpp"

class Tool {
public:
    Tool(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Rule> &Rules(void) const { return m_Rules; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Variables;
    std::vector<Rule> m_Rules;
};