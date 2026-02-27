#include "obfstr.hpp"
#include "ninsys.hpp"
#include <iostream>
#include "consolestart.hpp"
std::unordered_map<std::string, SysCommand> sysCommands;
void initSysCommands() {
    sysCommands[H("status")] = {
    H("status"),
    [](const std::vector<std::string>&)->int {
        std::cout << H("State: Killin it\nJobs: 0 queued\nSysVinit: 2.75-4-ninkill\n");
        return 0;
    }
    };
    sysCommands[H("reboot")] = {
        H("reboot"),
        [](const std::vector<std::string>&)->int {
            return 3;
        }
    };
    sysCommands[H("devices")] = {
        H("devices"),
        [](const std::vector<std::string>&)->int {
            printDevices();
            return 0;
        }
    };
    sysCommands[H("shutdown")] = {
        H("shutdown"),
        [](const std::vector<std::string>&)->int {
            EXIT(0);
            return 0;
        }
    };
    sysCommands[H("help")] = {
        H("help"),
        [](const std::vector<std::string>&)->int {
            std::cout << H("Available nin-sys commands:\n");
            for (auto& [k, v] : sysCommands) {
                std::cout << H("  ") << k << H("\n");
            }
            return 0;
        }
    };
}
int nin_sys_cmd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << H("Usage: nin-sys <command>\n");
        return 0;
    }
    auto it = sysCommands.find(args[1]);
    if (it == sysCommands.end()) {
        std::cout << H("Unknown nin-sys command\n");
        return 0;
    }
    return it->second.action(args);
}