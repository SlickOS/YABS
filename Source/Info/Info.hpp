#pragma once

#include <vector>
#include <map>
#include <string>

#include <yaml-cpp/yaml.h>

class Architecture;
class Configuration;
class Project;
class Workspace;

class Tools;
class Files;
class Flags;

class Tool;

//===========================================================================//
// Tool                                                                      //
//===========================================================================//
class Tool {
public:
    enum class Type {
        Compiler,
        Linker,
        Shell
    };

    Tool(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    Tool::Type GetType(void) const { return m_Type; }
    const std::map<std::string, std::string> &GetPlatforms(void) const { return m_Platforms; }

private:
    std::string m_Name;
    Tool::Type m_Type;
    std::map<std::string, std::string> m_Platforms;
};

//===========================================================================//
// ProjectTool                                                               //
//===========================================================================//
class ProjectTool {
public:
    enum class Type {
        Compiler,
        Linker,
        Shell
    };

    ProjectTool(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const std::string &GetPlatform(void) const { return m_Platform; }
    ProjectTool::Type GetType(void) const { return m_Type; }
    const std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > &GetDirectories(void) const { return m_Directories; }
    const std::map<std::string, std::string> &GetFiles(void) const { return m_Files; }

private:
    std::string m_Name;
    std::string m_Platform;
    ProjectTool::Type m_Type;
    std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > m_Directories;
    std::map<std::string, std::string> m_Files;
};

//===========================================================================//
// Configuration                                                             //
//===========================================================================//
class Configuration {
public:
    Configuration(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const std::map<std::string, std::string> &GetFlags(void) const { return m_Flags; }

private:
    std::string m_Name;
    std::map<std::string, std::string> m_Flags;
};

//===========================================================================//
// Project                                                                   //
//===========================================================================//
class Project {
public:
    Project(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const std::vector<std::string> &GetConfigurations(void) const { return m_Configurations; }
    const std::vector<ProjectTool> &GetTools(void) const { return m_Tools; }

private:
    std::string m_Name;
    std::vector<std::string> m_Configurations;
    std::vector<ProjectTool> m_Tools;
};

//===========================================================================//
// Job                                                                       //
//===========================================================================//
class Job {
public:
    Job(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const std::vector<std::string> &GetTasks(void) const { return m_Tasks; }
    const std::vector<std::string> &GetDependencies(void) const { return m_Dependencies; }

private:
    std::string m_Name;
    std::vector<std::string> m_Tasks;
    std::vector<std::string> m_Dependencies;
};

//===========================================================================//
// Workspace                                                                 //
//===========================================================================//
class Workspace {
public:
    Workspace(void) {}
    bool Parse(const YAML::Node &node);

    const std::vector<Tool> &GetTools(void) const { return m_Tools; }
    const std::vector<Configuration> &GetConfigurations(void) const { return m_Configurations; }
    const std::map<std::string, std::string> &GetFlags(void) const { return m_Flags; }
    const std::vector<Project> &GetProjects(void) const { return m_Projects; }
    const std::vector<Job> &GetJobs(void) const { return m_Jobs; }

private:
    std::vector<Tool> m_Tools;
    std::vector<Configuration> m_Configurations;
    std::map<std::string, std::string> m_Flags;
    std::vector<Project> m_Projects;
    std::vector<Job> m_Jobs;
};

// //===========================================================================//
// // Tool                                                                      //
// //===========================================================================//
// class Tool {
// public:
//     enum class Type {
//         Compiler,
//         Linker,
//         FileManipulation
//     };

//     Tool(void) {}
//     ~Tool(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetName(void) const { return m_Name; }
//     Tool::Type GetType(void) const { return m_Type; }

// protected:
//     std::string m_Name;
//     Tool::Type m_Type;
// };

// //===========================================================================//
// // Tools                                                                     //
// //===========================================================================//
// class Tools {
// public:
//     Tools(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetC(void) const { return m_C; }
//     const std::string &GetCXX(void) const { return m_CXX; }
//     const std::string &GetASM(void) const { return m_ASM; }
//     const std::string &GetLD(void) const { return m_LD; }

// private:
//     std::string m_C;
//     std::string m_CXX;
//     std::string m_ASM;
//     std::string m_LD;
// };

// //===========================================================================//
// // Files                                                                     //
// //===========================================================================//
// class Files {
// public:
//     Files(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::vector<std::string> &GetSources(void) const { return m_Sources; }
//     const std::vector<std::string> &GetIncludes(void) const { return m_Includes; }
//     const std::vector<std::string> &GetLibraries(void) const { return m_Libraries; }

// private:
//     std::vector<std::string> m_Sources;
//     std::vector<std::string> m_Includes;
//     std::vector<std::string> m_Libraries;
// };

// //===========================================================================//
// // Flags                                                                     //
// //===========================================================================//
// class Flags {
// public:
//     Flags(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetC(void) const { return m_C; }
//     const std::string &GetCXX(void) const { return m_CXX; }
//     const std::string &GetASM(void) const { return m_ASM; }
//     const std::string &GetLD(void) const { return m_LD; }

// private:
//     std::string m_C;
//     std::string m_CXX;
//     std::string m_ASM;
//     std::string m_LD;
// };

// //===========================================================================//
// // Architecture                                                              //
// //===========================================================================//
// class Architecture {
// public:
//     Architecture(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetName(void) const { return m_Name; }
//     const Tools &GetTools(void) const { return m_Tools; }
//     const Flags &GetFlags(void) const { return m_Flags; }

// private:
//     std::string m_Name;
//     Tools m_Tools;
//     Flags m_Flags;
// };

// //===========================================================================//
// // Configuration                                                             //
// //===========================================================================//
// class Configuration {
// public:
//     Configuration(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetName(void) const { return m_Name; }
//     const Flags &GetFlags(void) const { return m_Flags; }

// private:
//     std::string m_Name;
//     Flags m_Flags;
// };

// //===========================================================================//
// // Project                                                                   //
// //===========================================================================//
// class Project {
// public:
//     Project(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetName(void) const { return m_Name; }
//     const Flags &GetFlags(void) const { return m_Flags; }
//     const Files &GetFiles(void) const { return m_Files; }

// private:
//     std::string m_Name;
//     Flags m_Flags;
//     Files m_Files;
// };

// //===========================================================================//
// // Workspace                                                                 //
// //===========================================================================//
// class Workspace {
// public:
//     Workspace(void) {}
//     bool Parse(const YAML::Node &node);

//     const std::string &GetName(void) const { return m_Name; }
//     const Flags &GetFlags(void) const { return m_Flags; }
//     const std::string &GetOutputBinary(void) const { return m_OutputBinary; }
//     const std::string &GetOutputObject(void) const { return m_OutputObject; }

//     const std::vector<Architecture> &GetArchitectures(void) const { return m_Architectures; }
//     const std::vector<Configuration> &GetConfigurations(void) const { return m_Configurations; }
//     const std::vector<Project> &GetProjects(void) const { return m_Projects; }

// private:
//     std::string m_Name;
//     Flags m_Flags;
//     std::string m_OutputBinary;
//     std::string m_OutputObject;

//     std::vector<Architecture> m_Architectures;
//     std::vector<Configuration> m_Configurations;
//     std::vector<Project> m_Projects;
// };