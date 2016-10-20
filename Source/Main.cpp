#include <iostream>

#include "Configuration.hpp"
#include "Platform.hpp"
#include "Project.hpp"
#include "Target.hpp"
#include "Tool.hpp"
#include "Util.hpp"
#include "YABS.hpp"

#include <yaml-cpp/yaml.h>

int main(int argc, char **argv) {
    std::string config = "Build.yaml";
    std::string target;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "You don't get any help." << std::endl;
        }
        else if (arg == "-f" || arg == "--file") {
            if (argc > i + 1) {
                config = argv[++i];
            }
            else {
                std::cout << "Expected build configuration file." << std::endl;
                return -1;
            }
        }
        else {
            target = argv[i];
        }
    }

    if (target == "?") {
        std::cout << "You don't get any help." << std::endl;
    }

    std::vector<Configuration> configurations;
    std::vector<Platform> platforms;
    std::vector<Project> projects;
    std::vector<Target> targets;

    std::vector<Tool> tools;

    // Parse the configuration file.
    bool status = YABS::Parse(config, configurations, platforms, projects, targets);
    if (!status) {
        std::cerr << "Errors found in parsing." << std::endl;
        return -1;
    }

    status = YABS::Parse(tools);
    if (!status) {
        std::cerr << "Errors found in parsing." << std::endl;
        return -3;
    }

    // Select the target.
    Target select;
    if (target.empty()) {
        target = targets[0].Name();
        select = targets[0];
    }
    else {
        status = false;
        for (auto t : targets) {
            if (target == t.Name()) {
                status = true;
                select = t;
                break;
            }
        }
    }
    if (!status) {
        std::cerr << "Target not found: " << target << std::endl;
        return -2;
    }

    // Execute the target.
    for (auto project : projects) {
        YABS::Execute(select, project, configurations, platforms, projects, targets, tools);
    }

    // YAML::Node root = YAML::LoadFile(config);

    // // Parse All Configurations
    // if (root["Configurations"]) {
    //     for (auto node : root["Configurations"]) {
    //         Configuration configuration;
    //         configuration.Parse(node);
    //         configurations.push_back(configuration);
    //     }
    // }

    // // Parse All Architectures
    // if (root["Platforms"]) {
    //     for (auto node : root["Platforms"]) {
    //         Platform platform;
    //         platform.Parse(node);
    //         platforms.push_back(platform);
    //     }
    // }

    // // Parse All Projects
    // if (root["Projects"]) {
    //     for (auto node : root["Projects"]) {
    //         Project project;
    //         project.Parse(node);
    //         projects.push_back(project);
    //     }
    // }
    // else {
    //     Util::PrintError("No projects defined.", root);
    // }

    // // Parse All Targets
    // if (root["Targets"]) {
    //     for (auto node : root["Targets"]) {
    //         Target target;
    //         target.Parse(node);
    //         targets.push_back(target);
    //     }
    // }
    // else {
    //     Util::PrintError("No targets defined.", root);
    // }

    // for (auto project : projects) {
    //     std::cout << "- " << project.Name() << std::endl;
    //     std::cout << "  Variables:" << std::endl;
    //     for (auto variable : project.Variables()) {
    //         std::cout << "  - " << variable.first;
    //         std::cout << " = " << variable.second;
    //         std::cout << std::endl;
    //     }
    //     std::cout << "  Sub-Projects:" << std::endl;
    //     for (auto proj : project.SubProjects()) {
    //         std::cout << "  - " << proj.Name() << std::endl;
    //         std::cout << "    Variables:" << std::endl;
    //         for (auto variable : proj.Variables()) {
    //             std::cout << "    - " << variable.first;
    //             std::cout << " = " << variable.second;
    //             std::cout << std::endl;
    //         }
    //     }
    // }

    return 0;
}

// else if (arg == "-t" || arg == "--list-tools") {
//     std::cout << "Global Tools:" << std::endl;
//     for (auto file : Util::FindFiles("/etc/yabs", "yabs")) {
//         Tool tool;
//         tool.Parse(YAML::LoadFile(file));
//         std::cout << "- " << tool.Name() << std::endl;
//         std::cout << "  Variables:" << std::endl;
//         for (auto variable : tool.Variables()) {
//             std::cout << "    " << variable.first;
//             std::cout << " = " << variable.second;
//             std::cout << std::endl;
//         }
//         std::cout << "  Rules:" << std::endl;
//         for (auto rule : tool.Rules()) {
//             std::cout << "  - " << rule.Name() << std::endl;
//             std::cout << "    Arguments:" << std::endl;
//             for (auto argument : rule.Arguments()) {
//                 std::cout << "    - " << argument << std::endl;
//             }
//             std::cout << "    Commands:" << std::endl;
//             for (auto command : rule.Commands()) {
//                 std::cout << "      " << command.first;
//                 std::cout << " = " << command.second;
//                 std::cout << std::endl;
//             }
//         }
//     }
//     std::cout << "User Tools:" << std::endl;
//     for (auto file : Util::FindFiles("~/.yabs", "yabs")) {
//         Tool tool;
//         tool.Parse(YAML::LoadFile(file));
//         std::cout << "- " << tool.Name() << std::endl;
//         std::cout << "  Variables:" << std::endl;
//         for (auto variable : tool.Variables()) {
//             std::cout << "    " << variable.first;
//             std::cout << " = " << variable.second;
//             std::cout << std::endl;
//         }
//     }
//     std::cout << "Workspace Tools:" << std::endl;
//     for (auto file : Util::FindFiles(".yabs", "yabs")) {
//         Tool tool;
//         tool.Parse(YAML::LoadFile(file));
//         std::cout << "- " << tool.Name() << std::endl;
//         std::cout << "  Variables:" << std::endl;
//         for (auto variable : tool.Variables()) {
//             std::cout << "    " << variable.first;
//             std::cout << " = " << variable.second;
//             std::cout << std::endl;
//         }
//     }
// }