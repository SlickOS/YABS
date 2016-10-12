#include <iostream>

#include "Util.hpp"
#include "Tool.hpp"

#include <yaml-cpp/yaml.h>

int main(int argc, char **argv) {
    std::string config = "Build.yml";
    std::string target = "Build";

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
        else if (arg == "-t" || arg == "--list-tools") {
            std::cout << "Global Tools:" << std::endl;
            for (auto file : Util::FindFiles("BTool", "yml")) {
                Tool tool;
                tool.Parse(YAML::LoadFile(file));
                std::cout << "- " << tool.Name() << std::endl;
                std::cout << "  Variables:" << std::endl;
                for (auto variable : tool.Variables()) {
                    std::cout << "    " << variable.first;
                    std::cout << " = " << variable.second;
                    std::cout << std::endl;
                }
                std::cout << "  Rules:" << std::endl;
                for (auto rule : tool.Rules()) {
                    std::cout << "  - " << rule.Name() << std::endl;
                    std::cout << "    Arguments:" << std::endl;
                    for (auto argument : rule.Arguments()) {
                        std::cout << "    - " << argument << std::endl;
                    }
                    std::cout << "    Commands:" << std::endl;
                    for (auto command : rule.Commands()) {
                        std::cout << "      " << command.first;
                        std::cout << " = " << command.second;
                        std::cout << std::endl;
                    }
                }
            }
            std::cout << "User Tools:" << std::endl;
            for (auto file : Util::FindFiles("~/.btool", "yml")) {
                Tool tool;
                tool.Parse(YAML::LoadFile(file));
                std::cout << "- " << tool.Name() << std::endl;
                std::cout << "  Variables:" << std::endl;
                for (auto variable : tool.Variables()) {
                    std::cout << "    " << variable.first;
                    std::cout << " = " << variable.second;
                    std::cout << std::endl;
                }
            }
            std::cout << "Workspace Tools:" << std::endl;
            for (auto file : Util::FindFiles(".btool", "yml")) {
                Tool tool;
                tool.Parse(YAML::LoadFile(file));
                std::cout << "- " << tool.Name() << std::endl;
                std::cout << "  Variables:" << std::endl;
                for (auto variable : tool.Variables()) {
                    std::cout << "    " << variable.first;
                    std::cout << " = " << variable.second;
                    std::cout << std::endl;
                }
            }
        }
        else {
            target = argv[i];
        }
    }

    // std::vector<Tool> tools;
    // for (auto file : Util::FindFiles("BTool", "yml")) {
    //     Tool tool;
    //     tool.Parse(YAML::LoadFile(file));
    //     tools.push_back(tool);
    // }

    // for (auto tool : tools) {
    //     std::cout << "Name: " << tool.Name() << std::endl;
    //     std::cout << "Variables:" << std::endl;
    //     for (auto variable : tool.Variables()) {
    //         std::cout << "  " << variable.first;
    //         std::cout << " = " << variable.second;
    //         std::cout << std::endl;
    //     }
    // }

    return 0;
}