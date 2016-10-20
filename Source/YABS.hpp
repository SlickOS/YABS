#pragma once

#include <string>
#include <vector>

#include "Configuration.hpp"
#include "Platform.hpp"
#include "Project.hpp"
#include "Target.hpp"
#include "Tool.hpp"

namespace YABS {
    bool Parse(const std::string &fileName, std::vector<Configuration> &configurations, std::vector<Platform> &platforms, std::vector<Project> &projects, std::vector<Target> &targets);
    bool Parse(std::vector<Tool> &tools);

    bool Execute(const Target &target, const Project &project, const std::vector<Configuration> &configurations, const std::vector<Platform> &platforms, const std::vector<Project> &projects, const std::vector<Target> &targets, const std::vector<Tool> &tools);
    bool Execute(const Command &command, const std::string &target, const std::string &project, const std::string &platform, const std::string &configuration, const std::map<std::string, std::string> &vars, const std::vector<Tool> &tools);

    bool Expand(std::map<std::string, std::string> &variables);
    bool Expand(std::string &variable, std::map<std::string, std::string> &variables);

    bool IsIdentifierChar(char c);
    bool IsFuncIdentifierChar(char c);

    bool ParseFunctions(std::string &value);
    bool HandleFunction(std::string &function, std::vector<std::string> &args);
}