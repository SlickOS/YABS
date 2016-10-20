#include "YABS.hpp"

#include <iostream>

#include "Util.hpp"

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
                    for (auto command : target.Commands()) {
                        YABS::Execute(command, target.Name(), project.Name(), std::string(), config.Name(), variables, tools);
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

bool YABS::Execute(const Command &command,
                const std::string &target,
                const std::string &project,
                const std::string &platform,
                const std::string &configuration,
                const std::map<std::string, std::string> &vars,
                const std::vector<Tool> &tools) {
    std::string type = command.Type().first;
    std::string value = command.Type().second;

    for (auto var : vars) {
        //std::cout << var.first << " = " << var.second << std::endl;
        value = Util::ReplaceString(value, "$" + var.first, var.second);
    }

    auto loc = value.find("+Find");
    while (loc != std::string::npos) {
        int parentheses = 1;
        for (size_t i = loc + 6; i < value.size(); i++) {
            if (value[i] == '(') {
                parentheses++;
            }
            else if (value[i] == ')') {
                parentheses--;
                if (parentheses == 0) {
                    auto strX = value.substr(loc + 6, i - (loc + 6));
                    auto str = strX;
                    for (auto var : vars) {
                        //std::cout << var.first << " = " << var.second << std::endl;
                        str = Util::ReplaceString(str, "$" + var.first, var.second);
                    }
                    str = Util::Strip(str);
                    auto split = Util::Split(str, ',');
                    for (auto s : split) {
                        s = Util::Strip(s);
                    }
                    split[1] = split[1].substr(3, split[1].size() - 1);
                    auto files = Util::FindFiles(split[0], split[1]);
                    std::string fileStr;
                    for (auto file : files) {
                        fileStr += file + " ";
                    }
                    value = Util::ReplaceString(value, value.substr(loc, i - loc + 1), fileStr);
                    break;
                }
            }
        }
        loc = value.find("+Find");
    }

    value = Util::ReplaceString(value, "+Project", project);
    value = Util::ReplaceString(value, "+Platform", platform);
    value = Util::ReplaceString(value, "+Configuration", configuration);

    if (type == "Tool") {
        auto split = Util::Split(value, ' ');
        for (auto tool : tools) {
            if (split[0] == tool.Name()) {
                std::string taskStr;
                for (size_t i = 1; i < split.size(); i++) {
                    taskStr += split[i];
                    taskStr += " ";
                }
                split.clear();
                split = Util::Split(taskStr, '(');
                taskStr = split[0];
                std::string args;
                for (size_t i = 1; i < split.size(); i++) {
                    args += "(";
                    args += split[i];
                }

                args = Util::Strip(args);
                //std::cout << args << std::endl;

                Task task;
                for (auto t : tool.Tasks()) {
                    if (t.Name() == taskStr) {
                        task = t;
                        break;
                    }
                }

                std::cout << args << std::endl;

                std::map<std::string, std::string> taskVar;
                for (auto v : task.Variables()) {

                }
            }
        }
    }
    else if (type == "Shell") {
        std::cout << command.Type().second << std::endl;
    }
    else if (type == "Iterate") {
        std::cout << command.Type().second << std::endl;
    }
}