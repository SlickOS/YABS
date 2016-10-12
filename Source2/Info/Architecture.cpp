// #include "Info.hpp"

// #include <iostream>
// #include <string>

// #include "yaml-cpp/yaml.h"

// bool Architecture::Parse(const YAML::Node &node) {
//     if (node["Name"]) m_Name = node["Name"].as<std::string>();

//     if (node["Flags"]) {
//         Flags flags;
//         flags.Parse(node["Flags"]);
//         m_Flags = flags;
//     }

//     if (node["Tools"]) {
//         Tools tools;
//         tools.Parse(node["Tools"]);
//         m_Tools = tools;
//     }

//     return true;
// }