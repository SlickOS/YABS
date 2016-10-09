#include <iostream>

#include "Info/Info.hpp"
#include "Util.hpp"

#include <yaml-cpp/yaml.h>

int main(int argc, char **argv) {
    std::string buildConfig = "Build.yml";

    std::string cmd = "default";
    if (argc == 2) {
        cmd = argv[1];
    }

    if (cmd == "clean") {
        Util::CleanDir("Build");
        return 0;
    }

    Workspace workspace;
    workspace.Parse(YAML::LoadFile(buildConfig));

    // std::cout << "Workspace: " << workspace.GetName() << std::endl;
    // if (!workspace.GetFlags().GetC().empty()) std::cout << "  C Flags: " << workspace.GetFlags().GetC() << std::endl;
    // if (!workspace.GetFlags().GetCXX().empty()) std::cout << "  C++ Flags: " << workspace.GetFlags().GetCXX() << std::endl;
    // if (!workspace.GetFlags().GetASM().empty()) std::cout << "  Assembler Flags: " << workspace.GetFlags().GetASM() << std::endl;
    // if (!workspace.GetFlags().GetLD().empty()) std::cout << "  Linker Flags: " << workspace.GetFlags().GetLD() << std::endl;

    // if (!workspace.GetOutputBinary().empty()) std::cout << "  Output Binary: " << workspace.GetOutputBinary() << std::endl;

    // if (!workspace.GetArchitectures().empty()) {
    //     for (Architecture arch : workspace.GetArchitectures()) {
    //         if (!arch.GetName().empty()) std::cout << "  Arch: " << arch.GetName() << std::endl;
    //         if (!arch.GetTools().GetC().empty()) std::cout << "    C Compiler: " << arch.GetTools().GetC() << std::endl;
    //         if (!arch.GetTools().GetCXX().empty()) std::cout << "    C++ Compiler: " << arch.GetTools().GetCXX() << std::endl;
    //         if (!arch.GetTools().GetASM().empty()) std::cout << "    Assembler: " << arch.GetTools().GetASM() << std::endl;
    //         if (!arch.GetTools().GetLD().empty()) std::cout << "    Linker: " << arch.GetTools().GetLD() << std::endl;
    //         if (!arch.GetFlags().GetC().empty()) std::cout << "    C Flags: " << arch.GetFlags().GetC() << std::endl;
    //         if (!arch.GetFlags().GetCXX().empty()) std::cout << "    C++ Flags: " << arch.GetFlags().GetCXX() << std::endl;
    //         if (!arch.GetFlags().GetASM().empty()) std::cout << "    Assembler Flags: " << arch.GetFlags().GetASM() << std::endl;
    //         if (!arch.GetFlags().GetLD().empty()) std::cout << "    Linker Flags: " << arch.GetFlags().GetLD() << std::endl;
    //     }
    // }

    // if (!workspace.GetConfigurations().empty()) {
    //     for (Configuration config : workspace.GetConfigurations()) {
    //         std::cout << "  Config: " << config.GetName() << std::endl;
    //         if (!config.GetFlags().GetC().empty()) std::cout << "    C Flags: " << config.GetFlags().GetC() << std::endl;
    //         if (!config.GetFlags().GetCXX().empty()) std::cout << "    C++ Flags: " << config.GetFlags().GetCXX() << std::endl;
    //         if (!config.GetFlags().GetASM().empty()) std::cout << "    Assembler Flags: " << config.GetFlags().GetASM() << std::endl;
    //         if (!config.GetFlags().GetLD().empty()) std::cout << "    Linker Flags: " << config.GetFlags().GetLD() << std::endl;
    //     }
    // }

    // if (!workspace.GetProjects().empty()) {
    //     for (Project project : workspace.GetProjects()) {
    //         std::cout << "  Project: " << project.GetName() << std::endl;
    //         if (!project.GetFlags().GetC().empty()) std::cout << "    C Flags: " << project.GetFlags().GetC() << std::endl;
    //         if (!project.GetFlags().GetCXX().empty()) std::cout << "    C++ Flags: " << project.GetFlags().GetCXX() << std::endl;
    //         if (!project.GetFlags().GetASM().empty()) std::cout << "    Assembler Flags: " << project.GetFlags().GetASM() << std::endl;
    //         if (!project.GetFlags().GetLD().empty()) std::cout << "    Linker Flags: " << project.GetFlags().GetLD() << std::endl;
    //         if (!project.GetFiles().GetSources().empty()) {
    //             std::cout << "    Source Directories: ";
    //             for (std::string dir : project.GetFiles().GetSources()) std::cout << dir << " ";
    //             std::cout << std::endl;
    //         }
    //         if (!project.GetFiles().GetIncludes().empty()) {
    //             std::cout << "    Include Directories: ";
    //             for (std::string dir : project.GetFiles().GetIncludes()) std::cout << dir << " ";
    //             std::cout << std::endl;
    //         }
    //         if (!project.GetFiles().GetLibraries().empty()) {
    //             std::cout << "    Library Directories: ";
    //             for (std::string dir : project.GetFiles().GetLibraries()) std::cout << dir << " ";
    //             std::cout << std::endl;
    //         }
    //     }
    // }

    // DO THE BUILD PROCESS!!
    for (auto project : workspace.GetProjects()) {
        for (auto config : workspace.GetConfigurations()) {
            for (auto arch : workspace.GetArchitectures()) {
                auto objOut = workspace.GetOutputObject();
                objOut = Util::ReplaceString(objOut, "%(Architecture)", arch.GetName());
                objOut = Util::ReplaceString(objOut, "%(Configuration)", config.GetName());
                objOut = Util::ReplaceString(objOut, "%(Project)", project.GetName());

                auto binOut = workspace.GetOutputBinary();
                binOut = Util::ReplaceString(binOut, "%(Architecture)", arch.GetName());
                binOut = Util::ReplaceString(binOut, "%(Configuration)", config.GetName());
                binOut = Util::ReplaceString(binOut, "%(Project)", project.GetName());

                std::vector<std::string> srcC;
                std::vector<std::string> srcCXX;
                std::vector<std::string> srcASM;

                if (!project.GetFiles().GetSources().empty()) {
                    for (auto dir : project.GetFiles().GetSources()) {
                        auto curC = Util::FindFiles(dir, "c");
                        srcC.insert(std::end(srcC), std::begin(curC), std::end(curC));
                        auto curCXX = Util::FindFiles(dir, "cpp");
                        srcCXX.insert(std::end(srcCXX), std::begin(curCXX), std::end(curCXX));
                        auto curASM = Util::FindFiles(dir, "asm");
                        srcASM.insert(std::end(srcASM), std::begin(curASM), std::end(curASM));
                    }
                }

                std::vector<std::string> objC;
                std::vector<std::string> objCXX;
                std::vector<std::string> objASM;

                for (auto file : srcC) {
                    std::string obj = Util::ReplaceString(file, ".c", ".c.o");
                    std::string out = Util::ReplaceString(objOut, "%(Object)", obj);
                    objC.push_back(out);
                }
                for (auto file : srcCXX) {
                    std::string obj = Util::ReplaceString(file, ".cpp", ".cpp.o");
                    std::string out = Util::ReplaceString(objOut, "%(Object)", obj);
                    objCXX.push_back(out);
                }
                for (auto file : srcASM) {
                    std::string obj = Util::ReplaceString(file, ".asm", ".asm.o");
                    std::string out = Util::ReplaceString(objOut, "%(Object)", obj);
                    objASM.push_back(out);
                }

                std::string cmdC = arch.GetTools().GetC() + " ";
                cmdC += arch.GetFlags().GetC() + " ";
                cmdC += config.GetFlags().GetC() + " ";
                cmdC += project.GetFlags().GetC() + " ";
                cmdC += workspace.GetFlags().GetC() + " ";

                bool linkFlag = false;

                for (size_t i = 0; i < objC.size(); i++) {
                    if (!Util::NeedToRebuild(objC[i], srcC[i])/* && !Util::NeedToRebuild(objC[i], buildConfig)*/) continue;
                    linkFlag = true;
                    std::string cmd = cmdC + "-c -o " + objC[i] + " " + srcC[i];
                    std::cout << "Compiling " << srcC[i] << " -> " << objC[i] << std::endl;
                    //std::cout << cmd << std::endl;
                    Util::CreateDirFromFile(objC[i]);
                    system(cmd.c_str());
                }
                std::string cmdCXX = arch.GetTools().GetCXX() + " ";
                cmdCXX += arch.GetFlags().GetCXX() + " ";
                cmdCXX += config.GetFlags().GetCXX() + " ";
                cmdCXX += project.GetFlags().GetCXX() + " ";
                cmdCXX += workspace.GetFlags().GetCXX() + " ";
                for (size_t i = 0; i < objCXX.size(); i++) {
                    if (!Util::NeedToRebuild(objCXX[i], srcCXX[i])/* && !Util::NeedToRebuild(objC[i], buildConfig)*/) continue;
                    linkFlag = true;
                    std::string cmd = cmdCXX + "-c -o " + objCXX[i] + " " + srcCXX[i];
                    std::cout << "Compiling " << srcCXX[i] << " -> " << objCXX[i] << std::endl;
                    //std::cout << cmd << std::endl;
                    Util::CreateDirFromFile(objCXX[i]);
                    system(cmd.c_str());
                }
                std::string cmdASM = arch.GetTools().GetASM() + " ";
                cmdASM += arch.GetFlags().GetASM() + " ";
                cmdASM += config.GetFlags().GetASM() + " ";
                cmdASM += project.GetFlags().GetASM() + " ";
                cmdASM += workspace.GetFlags().GetASM() + " ";
                for (size_t i = 0; i < objASM.size(); i++) {
                    if (!Util::NeedToRebuild(objASM[i], srcASM[i])/* && !Util::NeedToRebuild(objC[i], buildConfig)*/) continue;
                    linkFlag = true;
                    std::string cmd = cmdASM + "-c -o " + objASM[i] + " " + srcASM[i];
                    std::cout << "Assembling " << srcASM[i] << " -> " << objASM[i] << std::endl;
                    //std::cout << cmd << std::endl;
                    Util::CreateDirFromFile(objASM[i]);
                    system(cmd.c_str());
                }

                if (linkFlag) {
                    std::string cmdLink = arch.GetTools().GetLD() + " ";
                    cmdLink += "-o " + binOut + " ";
                    for (auto obj : objC) {
                        cmdLink += obj + " ";
                    }
                    for (auto obj : objCXX) {
                        cmdLink += obj + " ";
                    }
                    for (auto obj : objASM) {
                        cmdLink += obj + " ";
                    }
                    Util::CreateDirFromFile(binOut);
                    cmdLink += arch.GetFlags().GetLD() + " " + config.GetFlags().GetLD() + " " + project.GetFlags().GetLD() + " " + workspace.GetFlags().GetLD() + " ";
                    std::cout << "Linking " << binOut << std::endl;
                    //std::cout << cmdLink << std::endl;
                    system(cmdLink.c_str());
                }
            }
        }
    }

    // std::vector<std::string> srcC;
    // for (std::string dir : project.GetFiles().GetIncludes)
    // srcC.insert(std::end(a), std::begin(b), std::end(b));
    // srcC. = Util::FindFiles("Source", "cpp");
    // for (auto file : files) {
    //     std::cout << file << std::endl;
    // }

    return 0;
}