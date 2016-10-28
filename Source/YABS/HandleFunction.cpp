#include "../YABS.hpp"
#include "../Util.hpp"

#include <iostream>

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