#pragma once

#include <vector>
#include <string>

#include <yaml-cpp/yaml.h>

class Architecture;
class Configuration;
class Project;
class Workspace;

class Tools;
class Files;
class Flags;

//===========================================================================//
// Tools                                                                     //
//===========================================================================//
class Tools {
public:
    Tools(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetC(void) const { return m_C; }
    const std::string &GetCXX(void) const { return m_CXX; }
    const std::string &GetASM(void) const { return m_ASM; }
    const std::string &GetLD(void) const { return m_LD; }

private:
    std::string m_C;
    std::string m_CXX;
    std::string m_ASM;
    std::string m_LD;
};

//===========================================================================//
// Files                                                                     //
//===========================================================================//
class Files {
public:
    Files(void) {}
    bool Parse(const YAML::Node &node);

    const std::vector<std::string> &GetSources(void) const { return m_Sources; }
    const std::vector<std::string> &GetIncludes(void) const { return m_Includes; }
    const std::vector<std::string> &GetLibraries(void) const { return m_Libraries; }

private:
    std::vector<std::string> m_Sources;
    std::vector<std::string> m_Includes;
    std::vector<std::string> m_Libraries;
};

//===========================================================================//
// Flags                                                                     //
//===========================================================================//
class Flags {
public:
    Flags(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetC(void) const { return m_C; }
    const std::string &GetCXX(void) const { return m_CXX; }
    const std::string &GetASM(void) const { return m_ASM; }
    const std::string &GetLD(void) const { return m_LD; }

private:
    std::string m_C;
    std::string m_CXX;
    std::string m_ASM;
    std::string m_LD;
};

//===========================================================================//
// Architecture                                                              //
//===========================================================================//
class Architecture {
public:
    Architecture(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const Tools &GetTools(void) const { return m_Tools; }
    const Flags &GetFlags(void) const { return m_Flags; }

private:
    std::string m_Name;
    Tools m_Tools;
    Flags m_Flags;
};

//===========================================================================//
// Configuration                                                             //
//===========================================================================//
class Configuration {
public:
    Configuration(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const Flags &GetFlags(void) const { return m_Flags; }

private:
    std::string m_Name;
    Flags m_Flags;
};

//===========================================================================//
// Project                                                                   //
//===========================================================================//
class Project {
public:
    Project(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const Flags &GetFlags(void) const { return m_Flags; }
    const Files &GetFiles(void) const { return m_Files; }

private:
    std::string m_Name;
    Flags m_Flags;
    Files m_Files;
};

//===========================================================================//
// Workspace                                                                 //
//===========================================================================//
class Workspace {
public:
    Workspace(void) {}
    bool Parse(const YAML::Node &node);

    const std::string &GetName(void) const { return m_Name; }
    const Flags &GetFlags(void) const { return m_Flags; }
    const std::string &GetOutputBinary(void) const { return m_OutputBinary; }
    const std::string &GetOutputObject(void) const { return m_OutputObject; }

    const std::vector<Architecture> &GetArchitectures(void) const { return m_Architectures; }
    const std::vector<Configuration> &GetConfigurations(void) const { return m_Configurations; }
    const std::vector<Project> &GetProjects(void) const { return m_Projects; }

private:
    std::string m_Name;
    Flags m_Flags;
    std::string m_OutputBinary;
    std::string m_OutputObject;

    std::vector<Architecture> m_Architectures;
    std::vector<Configuration> m_Configurations;
    std::vector<Project> m_Projects;
};