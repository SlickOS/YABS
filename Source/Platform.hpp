#pragma once

#include <map>
#include <string>

#include <yaml-cpp/yaml.h>

class Platform {
public:
    Platform(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &Name(void) const { return m_Name; }
    const std::map<std::string, std::string> &Variables(void) const { return m_Variables; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Variables;
};