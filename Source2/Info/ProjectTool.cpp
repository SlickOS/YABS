#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

#include "../Util.hpp"

bool ProjectTool::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        std::cerr << "Tool missing name." << std::endl;
        return false;
    }

    if (node["Directories"]) {
        auto nodeDir = node["Directories"];
        for (auto it = nodeDir.begin(); it != nodeDir.end(); it++) {
            auto inner = *it;
            if (inner["Input"] && inner["Output"]) {
                std::vector<std::string> input = Util::Split(inner["Input"].as<std::string>(), ' ');
                std::vector<std::string> output = Util::Split(inner["Output"].as<std::string>(), ' ');
                std::string inputDir = input[0];
                std::string outputDir = output[0];
                std::string outputExt;

                if (output.size() == 2) {
                    outputExt = output[1];
                }

                std::pair<std::string, std::string> out(outputDir, outputExt);

                if (input.size() < 2) {
                    std::pair<std::string, std::string> in(inputDir, std::string());
                    m_Directories[in] = out;
                }
                for (size_t i = 1; i < input.size(); i++) {
                    std::pair<std::string, std::string> in(inputDir, input[i]);
                    m_Directories[in] = out;
                }
            }
            else if (inner["Input"]) {
                std::vector<std::string> input = Util::Split(inner["Input"].as<std::string>(), ' ');
                std::string inputDir = input[0];

                if (input.size() < 2) {
                    std::pair<std::string, std::string> in(inputDir, std::string());
                    m_Directories[in] = std::pair<std::string, std::string>();
                }
                for (size_t i = 1; i < input.size(); i++) {
                    std::pair<std::string, std::string> in(inputDir, input[i]);
                    m_Directories[in] = std::pair<std::string, std::string>();
                }
            }
            else {
                std::cerr << "Missing input or output directory." << std::endl;
                return false;
            }
            // for (auto i = inner.begin(); i != inner.end(); i++) {
            //     std::string name = i->first.as<std::string>();
            //     std::string value = i->second.as<std::string>();

            //     std::istringstream ss(value);
            //     while()

            //     m_Directories[name] = value;
            // }
        }
    }

    if (node["Files"]) {
        auto nodeFile = node["Files"];
        for (auto it = nodeFile.begin(); it != nodeFile.end(); it++) {
            auto inner = *it;
            for (auto i = inner.begin(); i != inner.end(); i++) {
                std::string name = i->first.as<std::string>();
                std::string value = i->second.as<std::string>();
                m_Files[name] = value;
            }
        }
    }

    // else {
    //     std::cerr << "Tool missing directories." << std::endl;
    //     return false;
    // }

    return true;
}

// istringstream iss(str1);
 
//     while (iss) {
//         string word;
//         iss >> word;
//         cout << word << endl;
//     }



    // if (node["Platforms"]) {
    //     auto nodePlatform = node["Platforms"];
    //     for (auto it = nodePlatform.begin(); it != nodePlatform.end(); it++) {
    //         auto inner = *it;
    //         for (auto i = inner.begin(); i != inner.end(); i++) {
    //             std::string name = i->first.as<std::string>();
    //             std::string command = i->second.as<std::string>();
    //             m_Platforms[name] = command;
    //         }
    //     }
    // }
    // else {
    //     std::cerr << "Tool missing platforms." << std::endl;
    //     return false;
    // }