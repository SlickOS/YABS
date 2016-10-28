#include "../YABS.hpp"
#include "../Util.hpp"

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
        auto size = args.size();
        for (size_t i = 0; i < size - 1; i++) {
            if (Util::NeedToRebuild(args[size - 1], args[i])) {
                return true;
            }
        }
    }
    return false;
}