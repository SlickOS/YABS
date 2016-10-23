#include "YABS.hpp"

#include <csignal>
#include <iostream>

#include "Util.hpp"

static bool g_Persistence = false;
static std::string g_PersistentString;

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

bool YABS::Execute(const Command &command,
                const std::string &target,
                const std::string &project,
                const std::string &platform,
                const std::string &configuration,
                const std::map<std::string, std::string> &vars,
                const std::vector<Tool> &tools) {
    // Get Command Information
    std::string type = command.Type().first;
    std::string value = command.Type().second;

    std::map<std::string, std::string> currentVars = vars;

    value = Util::ReplaceString(value, "+Project", project);
    value = Util::ReplaceString(value, "+Platform", platform);
    value = Util::ReplaceString(value, "+Configuration", configuration);

    // Expand Variables in Command
    bool status = YABS::Expand(value, currentVars);
    if (!status) {
        std::cerr << "Error expanding variables." << std::endl;
        return false;
    }

    // Parse Functions
    status = YABS::ParseFunctions(value);
    if (!status) {
        std::cerr << "Error parsing functions." << std::endl;
    }

    // Handle Command
    if (type == "Tool") {
        auto pos = value.find_first_of(" ");
        auto par = value.find_first_of("()");
        auto toolStr = value.substr(0, pos);
        auto taskStr = value.substr(pos + 1, par - pos - 1);
        std::vector<std::string> args;

        int parentheses = 0;
        auto start = par;
        while (par != std::string::npos) {
            if (value[par] == '(') {
                parentheses++;
            }
            else {
                parentheses--;
                if (parentheses == 0) {
                    auto argStr = value.substr(start + 1, par - start - 1);
                    args = Util::Split(argStr, ',');
                    for (auto &arg : args) {
                        Util::Strip(arg);
                    }

                    break;
                }
            }
            par = value.find_first_of("()", par + 1);
        }

        // Execute Task of Tool
        for (auto &tool : tools) {
            if (tool.Name() == toolStr) {
                for (auto &task : tool.Tasks()) {
                    if (task.Name() == taskStr) {
                        //std::cout << "Executing task '" << task.Name() << "' of tool '" << tool.Name() << "'" << std::endl;
                        std::map<std::string, std::string> taskVariables;

                        // Now Construct argument array
                        int i = 0;
                        for (auto &var : task.Variables()) {
                            taskVariables[var] = args[i++];
                        }
                        auto variables = Util::AppendVariables(tool.Variables(), taskVariables);
                        YABS::Expand(variables);

                        auto conds = task.Conditions();
                        if (YABS::HandleConditions(conds, variables)) {
                            // Execute the tool
                            for (auto &cmd : task.Commands()) {
                                if (!YABS::Execute(cmd, target, project, platform, configuration, variables, tools)) return false;
                                //ERROR-INDUCE
                            }
                        }
                    }
                }
            }
        }

    }
    else if (type == "Shell") {
        // Execute the shell command.
        if (YABS::Persistence()) {
            g_PersistentString += value + " && ";
        }
        else {
            auto status = std::system(value.c_str());
            if (status != 0) {
                if (WIFSIGNALED(status)) {
                    exit(SIGTERM);
                }
                return false;
            }
        }

        // std::cout << value << std::endl;
    }
    else if (type == "Iterate") {
        auto pos = value.find_first_of(" ");

        auto valVar = value.substr(0, pos);
        auto arrStr = value.substr(pos + 1);

        Util::Strip(arrStr);
        auto arr = Util::Split(arrStr, ' ');

        for (auto var : arr) {
            auto variables = Util::AppendVariables(vars, command.Variables());
            variables[valVar] = var;
            YABS::Expand(variables);

            // Check Conditions
            auto conditions = command.Conditions();
            //std::cout << "ABOUT TO HANDLE CONDITIONS..." << std::endl;
            //for (auto var : vars) {
            //    std::cout << "  " << var.first << " = " << var.second << std::endl;
            //}
            if (YABS::HandleConditions(conditions, variables)) {
                for (auto &cmd : command.Commands()) {
                    YABS::Execute(cmd, target, project, platform, configuration, variables, tools);
                }
            }
        }
    }
    else if (type == "Persistence") {
        if (value == "Start") {
            YABS::SetPersistence(true);
        }
        else if (value == "End") {
            YABS::SetPersistence(false);
            g_PersistentString = g_PersistentString.substr(0, g_PersistentString.size() - 4);
            auto status = std::system(g_PersistentString.c_str());
            if (status != 0) {
                if (WIFSIGNALED(status)) {
                    exit(SIGTERM);
                }
                return false;
            }
            // std::cout << g_PersistentString << std::endl;
            g_PersistentString.clear();
        }
    }

    return true;
}

bool YABS::Expand(std::map<std::string, std::string> &variables) {
    for (auto &variable : variables) {
        YABS::Expand(variable.second, variables);
        YABS::ParseFunctions(variable.second);
        Util::Strip(variable.second);
    }
    return true;
}

bool YABS::Expand(std::string &value, std::map<std::string, std::string> &variables) {
    auto location = value.find("$");
    while (location != std::string::npos) {
        auto end = location + 1;
        while (YABS::IsIdentifierChar(value[end]) && end != std::string::npos) {
            end++;
        }
        // std::cout << "VAR: " << value.substr(location + 1, end - 2) << std::endl;
        auto varStr = value.substr(location + 1, end - location - 1);
        // std::cout << "VAR: " << varStr << std::endl;

        for (auto &var : variables) {
            if (var.first == varStr) {
                YABS::Expand(var.second, variables);
                value = Util::ReplaceString(value, value.substr(location, end - location), var.second);
                break;
            }
        }

        location = value.find("$", location + 1);
    }
    return true;
}

bool YABS::IsIdentifierChar(char c) {
    if (std::isalnum(c)) return true;
    if (c == '-' || c == '_') return true;
    if (c == '+' || c == '=') return true;
    return false;
}

bool YABS::IsFuncIdentifierChar(char c) {
    if (std::isalnum(c)) return true;
    if (c == '_') return true;
    return false;
}

bool YABS::ParseFunctions(std::string &value) {
    auto location = value.find("+");
    while (location != std::string::npos) {
        auto end = location + 1;
        if (location >= 1 && !YABS::IsIdentifierChar(value[location - 1])) {
            while (YABS::IsFuncIdentifierChar(value[end]) && end != std::string::npos) {
                end++;
            }
            auto funcStr = value.substr(location + 1, end - location - 1);
            if (!funcStr.empty()) {
                auto par = value.find_first_of("()", location);
                auto start = par;
                while (par != std::string::npos) {
                    if (value[par] == '(') {
                        auto str = value.substr(par);
                        YABS::ParseFunctions(str);
                        value = Util::ReplaceString(value, value.substr(par), str);
                    }
                    else if (value[par] == ')') {
                        auto argStr = value.substr(start + 1, par - start - 1);
                        auto args = Util::Split(argStr, ',');
                        for (auto &arg : args) {
                            Util::Strip(arg);
                        }

                        YABS::HandleFunction(funcStr, args);
                        value = Util::ReplaceString(value, value.substr(location, par - location + 1), funcStr);

                        break;
                    }
                    par++;
                }
            }
        }
        location = value.find("+", end);
    }
    return true;
}

bool YABS::HandleFunction(std::string &function, std::vector<std::string> &args) {
    if (function == "Find") {
        if (args.size() != 2) {
            std::cerr << "Wrong number of arguments for 'Find'." << std::endl;
            return false;
        }
        std::string suffix = args[1].substr(2);

        function.clear();
        auto files = Util::FindFiles(args[0], suffix);
        for (auto file : files) {
            function += file + " ";
        }

        Util::Strip(function);
    }
    else if (function == "AddPrefix") {
        if (args.size() != 2) {
            std::cerr << "Wrong number of arguments for 'AddPrefix'." << std::endl;
            return false;
        }

        function.clear();
        auto words = Util::Split(args[0], ' ');
        for (auto &word : words) {
            function += args[1] + word + " ";
        }

        Util::Strip(function);
    }
    else if (function == "AddSuffix") {
        if (args.size() != 2) {
            std::cerr << "Wrong number of arguments for 'AddSuffix'." << std::endl;
            return false;
        }

        function.clear();
        auto words = Util::Split(args[0], ' ');
        for (auto &word : words) {
            function += word + args[1] + " ";
        }

        Util::Strip(function);
    }
    else if (function == "Replace") {
        if (args.size() != 3) {
            std::cerr << "Wrong number of arguments for 'Find'." << std::endl;
            return false;
        }

        function = Util::ReplaceString(args[0], args[1], args[2]);
        Util::Strip(function);
    }
    else if (function == "Dir") {
        if (args.size() != 1) {
            std::cerr << "Wrong number of arguments for 'Dir'." << std::endl;
            return false;
        }

        //std::cout << "DIR!!!!!: " << args[0] << std::endl;

        function = Util::GetDirFromFile(args[0]);
        Util::Strip(function);
    }

    return true;
}

bool YABS::HandleConditions(std::vector<std::pair<std::string, std::string> > &conditions, std::map<std::string, std::string> &variables) {
    for (auto condition : conditions) {
        std::string value = condition.second;
        YABS::Expand(value, variables);
        YABS::ParseFunctions(value);
        auto words = Util::Split(value, ' ');
        for (auto &word : words) {
            Util::Strip(word);
        }
        if (!YABS::HandleCondition(condition.first, words)) {
            return false;
        }
    }
    return true;
}

bool YABS::HandleCondition(std::string &condition, std::vector<std::string> &args) {
    if (condition == "Newer") {
        if (args.empty()) return true;
        //std::cout << "ARGS: " << std::endl;
        //for (auto arg: args) {
        //    std::cout << "  " << arg << std::endl;
        //}
        auto size = args.size();
        for (size_t i = 0; i < size - 1; i++) {
            if (Util::NeedToRebuild(args[size - 1], args[i])) {
                return true;
            }
        }
    }
    return false;
}

bool YABS::Persistence(void) { return g_Persistence; }
void YABS::SetPersistence(bool persistence) { g_Persistence = persistence; }







    // for (auto var : vars) {
    //     //std::cout << var.first << " = " << var.second << std::endl;
    //     value = Util::ReplaceString(value, "$" + var.first, var.second);
    // }

    // // Parse Built-In Functions


    // auto loc = value.find("+Find");
    // while (loc != std::string::npos) {
    //     int parentheses = 1;
    //     for (size_t i = loc + 6; i < value.size(); i++) {
    //         if (value[i] == '(') {
    //             parentheses++;
    //         }
    //         else if (value[i] == ')') {
    //             parentheses--;
    //             if (parentheses == 0) {
    //                 auto strX = value.substr(loc + 6, i - (loc + 6));
    //                 auto str = strX;
    //                 for (auto var : vars) {
    //                     //std::cout << var.first << " = " << var.second << std::endl;
    //                     str = Util::ReplaceString(str, "$" + var.first, var.second);
    //                 }
    //                 str = Util::Strip(str);
    //                 auto split = Util::Split(str, ',');
    //                 for (auto s : split) {
    //                     s = Util::Strip(s);
    //                 }
    //                 split[1] = split[1].substr(3, split[1].size() - 1);
    //                 auto files = Util::FindFiles(split[0], split[1]);
    //                 std::string fileStr;
    //                 for (auto file : files) {
    //                     fileStr += file + " ";
    //                 }
    //                 value = Util::ReplaceString(value, value.substr(loc, i - loc + 1), fileStr);
    //                 break;
    //             }
    //         }
    //     }
    //     loc = value.find("+Find");
    // }

    // value = Util::ReplaceString(value, "+Project", project);
    // value = Util::ReplaceString(value, "+Platform", platform);
    // value = Util::ReplaceString(value, "+Configuration", configuration);

    // if (type == "Tool") {
    //     auto split = Util::Split(value, ' ');
    //     for (auto tool : tools) {
    //         if (split[0] == tool.Name()) {
    //             std::string taskStr;
    //             for (size_t i = 1; i < split.size(); i++) {
    //                 taskStr += split[i];
    //                 taskStr += " ";
    //             }
    //             split.clear();
    //             split = Util::Split(taskStr, '(');
    //             taskStr = split[0];
    //             std::string args;
    //             for (size_t i = 1; i < split.size(); i++) {
    //                 args += "(";
    //                 args += split[i];
    //             }

    //             args = Util::Strip(args);
    //             //std::cout << args << std::endl;

    //             Task task;
    //             for (auto t : tool.Tasks()) {
    //                 if (t.Name() == taskStr) {
    //                     task = t;
    //                     break;
    //                 }
    //             }

    //             std::cout << args << std::endl;

    //             std::map<std::string, std::string> taskVar;
    //             for (auto v : task.Variables()) {

    //             }
    //         }
    //     }
    // }
    // else if (type == "Shell") {
    //     std::cout << command.Type().second << std::endl;
    // }
    // else if (type == "Iterate") {
    //     std::cout << command.Type().second << std::endl;
    // }
// }