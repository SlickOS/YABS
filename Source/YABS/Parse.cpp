#include "YABS.hpp"

#include <algorithm>
#include <iostream>

#include "Util.hpp"

bool YABS::Parse(const std::string &fileName, std::vector<Configuration> &configurations, std::vector<Platform> &platforms, std::vector<Project> &projects, std::vector<Target> &targets) {
    YAML::Node root = YAML::LoadFile(fileName);

    bool status = true;

    // Parse All Configurations
    if (root["Configurations"]) {
        for (auto node : root["Configurations"]) {
            Configuration configuration;
            if (!configuration.Parse(node)) status = false;
            configurations.push_back(configuration);
        }
    }

    // Parse All Architectures
    if (root["Platforms"]) {
        for (auto node : root["Platforms"]) {
            Platform platform;
            if (!platform.Parse(node)) status = false;
            platforms.push_back(platform);
        }
    }

    // Parse All Projects
    if (root["Projects"]) {
        for (auto node : root["Projects"]) {
            Project project;
            if (!project.Parse(node)) status = false;
            projects.push_back(project);
        }
    }
    else {
        Util::PrintYAMLError("No projects defined.", root);
    }

    // Parse All Targets
    if (root["Targets"]) {
        for (auto node : root["Targets"]) {
            Target target;
            if (!target.Parse(node)) status = false;
            targets.push_back(target);
        }
    }
    else {
        Util::PrintYAMLError("No targets defined.", root);
    }

    return status;
}

bool YABS::Parse(std::vector<Tool> &tools) {
    for (auto file : Util::FindFiles("/etc/yabs", "yaml")) {
        Tool tool;
        tool.Parse(YAML::LoadFile(file));
        auto it = std::find_if(tools.begin(), tools.end(), [&n = tool](const Tool &t) { return t.Name() == n.Name(); });
        if (it != tools.end()) {
            *it = tool;
        }
        else {
            tools.push_back(tool);
        }
    }
    for (auto file : Util::FindFiles("~/.yabs", "yaml")) {
        Tool tool;
        tool.Parse(YAML::LoadFile(file));
        auto it = std::find_if(tools.begin(), tools.end(), [&n = tool](const Tool &t) { return t.Name() == n.Name(); });
        if (it != tools.end()) {
            *it = tool;
        }
        else {
            tools.push_back(tool);
        }
    }
    for (auto file : Util::FindFiles(".yabs", "yaml")) {
        Tool tool;
        tool.Parse(YAML::LoadFile(file));
        auto it = std::find_if(tools.begin(), tools.end(), [&n = tool](const Tool &t) { return t.Name() == n.Name(); });
        if (it != tools.end()) {
            *it = tool;
        }
        else {
            tools.push_back(tool);
        }
    }

    return true;
}