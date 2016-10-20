#pragma once

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>


class Command {
public:
    Command(void) {}
    bool Parse(const YAML::Node &node);

    const std::pair<std::string, std::string> &Type(void) const { return m_Type; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }
    const std::vector<Command> &Commands(void) const { return m_Commands; }

private:
    std::pair<std::string, std::string> m_Type;
    std::map<std::string, std::string> m_Variables;
    std::vector<Command> m_Commands;
};