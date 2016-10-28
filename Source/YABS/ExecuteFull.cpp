#include "../YABS.hpp"
#include "../Util.hpp"

#include <iostream>

bool YABS::Execute(const Target &target,
                    const Project &project,
                    const std::vector<Configuration> &configurations,
                    const std::vector<Platform> &platforms,
                    const std::vector<Project> &projects,
                    const std::vector<Target> &targets,
                    const std::vector<Tool> &tools) {
    bool status = false;

    // Deal with dependencies
    const std::vector<std::string> &deps = target.Dependencies();
    if (!deps.empty()) {
        for (auto dep : deps) {
            Target select;
            for (auto t : targets) {
                if (dep == t.Name()) {
                    select = t;
                    status = true;
                    break;
                }
            }
            if (!status) {
                std::cerr << "Dependency '" << dep << "' not found for target '" << target.Name() << "'." << std::endl;
            }
            if (!YABS::Execute(select, project, configurations, platforms, projects, targets, tools)) {
                std::cerr << "Dependency '" << dep << "' failed for target '" << target.Name() << "'." << std::endl;
                return false;
            }
        }
    }

    // Deal with subprojects
    const std::vector<Project> &subs = project.Projects();
    status = true;
    if (!subs.empty()) {
        for (auto sub : subs) {
            if (!YABS::Execute(target, sub, configurations, platforms, projects, targets, tools)) {
                std::cerr << "Subproject '" << sub.Name() << "' failed for project '" << project.Name() << "'." << std::endl;
                status = false;
            }
        }
        if (!status) {
            std::cerr << "Target '" << target.Name() << "' failed for project '" << project.Name() << "'." << std::endl;
        }
    }
    else {
        auto variablesTarget = target.Variables();
        auto variablesProject = Util::AppendVariables(variablesTarget, project.Variables());

        if (!platforms.empty()) {
            for (auto platform : platforms) {
                auto variablesPlatform = Util::AppendVariables(variablesProject, platform.Variables());
                if (!configurations.empty()) {
                    for (auto config : configurations) {
                        auto variables = Util::AppendVariables(variablesPlatform, config.Variables());
                    }
                }
                // Build It Directly
                else {
                    auto variables = variablesPlatform;
                }
            }
        }
        // Build It Directly
        else {
            if (!configurations.empty()) {
                for (auto config : configurations) {
                    auto variables = Util::AppendVariables(variablesProject, config.Variables());

                    // Expand Variables
                    bool status = YABS::Expand(variables);
                    if (!status) {
                        std::cerr << "Error expanding variables." << std::endl;
                        return false;
                    }

                    // Execute Commands
                    for (auto command : target.Commands()) {
                        status = YABS::Execute(command, target.Name(), project.Name(), std::string(), config.Name(), variables, tools);
                    }
                }
            }
            // Build It Directly
            else {
                auto variables = variablesProject;
            }
        }
        if (!status) {
            std::cerr << "Target '" << target.Name() << "' failed for project '" << project.Name() << "'." << std::endl;
        }
    }

    return status;
}