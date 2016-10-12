#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "Rule.hpp"

class Rule {
public:
    Rule(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::vector<std::string> &Arguments(void) const { return m_Arguments; }
    const std::map<std::string, std::string> &Commands(void) const { return m_Commands; }

private:
    std::string m_Name;
    std::vector<std::string> m_Arguments;
    std::map<std::string, std::string> m_Commands;
};