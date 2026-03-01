#include <util/obfstr.hpp>
#include <system/pkg.hpp>
#include <iostream>
#include <vector>
#include <string>
std::unordered_map<std::string, NeonCommand> neonCommands;
static std::string arg(const std::vector<std::string>& a, size_t i) {
    return (i < a.size()) ? a[i] : "";
}
void initNeon() {
    neonCommands[H("install")] = {
        H("install"),
        [](const std::vector<std::string>& a)->int {
            if (a.size() < 3) {
                std::cout << H("Usage: neon install <package>\n");
                return 0;
            }
            std::string pkg = a[2];
            if (pkg == H("vdd")) {
                std::cout << H("Error: archive discontinued\nThe virtual dynamic disk(vdd) is unstable on NINKILLos 1.3, we can not supply you defected copys of it.\n\n");
                return 0;
            }
            else if (pkg == H("forum")) {
                std::cout << H("The forum package is now hard installed on NINKILL 1.3\n");
                std::cout << H("See: www.nuebine.com/forum/news\n");
                return 0;
            }
            else if (pkg == H("echo")) {
                std::cout << H("Echo node sent to www.neudb.com/.echo\n");
                return 0;
            }
            else if (pkg == H("vi")) {
                std::cout << "Error: Editors are not suported on NINKILL 1.3\nSee: www.nuebine.com/os/\n";
                return 0;
            }
            std::cout << H("Could not find package ") << pkg << H(" in database www.nuedb.co.us, returned error 404.\n");
            return 0;
        }
    };
    neonCommands[H("remove")] = {
        H("remove"),
        [](auto& args)->int {
            std::string pkg = arg(args,1);
            std::cout << H("Removing ") << pkg << H("...\nDone\n");
            return 0;
        }
    };
    neonCommands[H("help")] = {
        H("help"),
        [](auto&)->int {
            std::cout << H("neon package manager\ncommands:\n|install\n|remove\n|help");
            return 0;
        }
    };
}
int neon_cmd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << H("Usage: neon <command> [args]\n");
        return 0;
    }
    auto it = neonCommands.find(args[1]);
    if (it == neonCommands.end()) {
        std::cout << H("neon: unknown command '")
            << args[1]
            << H("'\n");
        return 0;
    }
    return it->second.action(args);
}