#include "../YABS.hpp"
#include "../Util.hpp"

#include <iostream>
#include <csignal>

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
            YABS::PersistenceString() += value + " && ";
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
            YABS::PersistenceString() = YABS::PersistenceString().substr(0, YABS::PersistenceString().size() - 4);
            auto status = std::system(YABS::PersistenceString().c_str());
            if (status != 0) {
                if (WIFSIGNALED(status)) {
                    exit(SIGTERM);
                }
                return false;
            }
            // std::cout << g_PersistentString << std::endl;
            YABS::PersistenceString().clear();
        }
    }

    return true;
}