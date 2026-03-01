#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
struct NeonCommand {
    std::string name;
    std::function<int(const std::vector<std::string>&)> action;
};
extern std::unordered_map<std::string, NeonCommand> neonCommands;
void initNeon();
int neon_cmd(const std::vector<std::string>& args);