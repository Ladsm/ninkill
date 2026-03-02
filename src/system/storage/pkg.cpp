#include <util/obfstr.hpp>
#include <system/storage/pkg.hpp>
#include <ui/spiner.hpp>
#include <vfs/vfs.hpp>
#include <util/text/longtexts.h>
#include <programs/vi.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
const std::vector<std::string> ninfetch =
{
    H("                                                                       \n"),
    H("               ----++----                                              \n"),
    H("                   ||  AAA                                             \n"),
    H("++-----            ||   AAA      ---++---                              \n"),
    H("||    AA           ||    AA         ||                                 \n"),
    H("||     AA          ||     AA        ||                                 \n"),
    H("||     AA          ||     AA        || +-----------------------------+ \n"),
    H("||      AA         ||     AA        || |root@ninkill-live            | \n"),
    H("||      AA         ||     AA        || |OS: ninkill x86              | \n"),
    H("||      AA         ||      AA       || |Packages:                    | \n"),
    H("||      AA         ||      AA       || |Shell: bash 2.0              | \n"),
    H("||      AA         ||      AA       || |CPU: Intel(c) Pentium MMX 200| \n"),
    H("||       AA        ||      AA       || |MHz Memory: 32MB SDRAM       | \n"),
    H("||       AA        ||       AA      || |Disk (/): 10.3 MB - mfs      | \n"),
    H("||       AA        ||       AA      || |Disk (/mnt/): 5.05GB - mfs   | \n"),
    H("||        AA       ||        AA     || |Locale: en_US.UTF-8          | \n"),
    H("||         AA      ||        AAA    || +-----------------------------+ \n"),
    H("||          AA     ||          AA   ||                                 \n"),
    H("            AAA    ||           AAAA++                                 \n"),
    H("             AAA   ||             AA                                   \n"),
    H("              AAA  ||                                                  \n"),
    H("               AAA ||                                                  \n"),
    H("                AAA||                                                  \n"),
    H("               ----++---                                               \n"),
    H("                                                                       \n"),
};
std::unordered_map<std::string, NeonCommand> neonCommands;
package vdd = package(H("vdd"), H("Error: archive discontinued\nThe virtual dynamic disk(vdd) is unstable on NINKILLos 1.3, we can not supply you defected copys of it."), false, false);
package forum = package(H("forum"), H("The forum package is now hard installed on NINKILL 1.3\nSee: www.nuebine.com/forum/news"), false, false);
package echo = package(H("echo"), H("Echo node sent to www.neudb.com/.echo"), false, false);
package vi = package(H("vi"), H("vi installed!\nUsage: vi <filename>"), true, false);
package ninshow = package(H("ninshow"), H("Installed!\nWrite nin-show to see all the parts of your computer."), true, false);
std::vector<package> packagesz = { vdd, forum, echo, vi, ninshow };
static std::string arg(const std::vector<std::string>& a, size_t i) {
    return (i < a.size()) ? a[i] : "";
}
void initNeon() {
    neonCommands[H("install")] = {
        H("install"),
        [](const std::vector<std::string>& a) -> int {
            if (a.size() < 3) {
                std::cout << H("Usage: neon install <package>\n");
                return 0;
            }
            std::string pkgName = a[2];
            for (size_t i = 0; i < packagesz.size(); i++) {
                if (packagesz[i].name == pkgName) {
                    if (packagesz[i].willDownload) {
                        progressbar(20);
                        packagesz[i].downloaded = true;
                        VNode* bin = resolvePath(H("/bin"));
                        if (bin) {
                            VNode* exe = mkfile(bin, pkgName + H(".exc"), giberspeak());
                            exe->isExec = true;
                            if (pkgName == H("vi")) {
                                exe->execFunc = [](const std::vector<std::string>& args) { Vi(args); return 0; };
                            }
                            else if (pkgName == H("ninshow")) {
                                exe->execFunc = [](const std::vector<std::string>& args) {
                                    for (const auto& line : ninfetch) std::cout << line;
                                    return 0;
                                    };
                                }
                            }
                            std::cout << packagesz[i].message << '\n';
                        }
                        else {
                            std::cout << packagesz[i].message << '\n';
                    }
                    return 0;
                }
            }
            std::cout << H("Could not find package ") << pkgName << H("\n");
            return 0;
        }
    };
    neonCommands[H("remove")] = {
        H("remove"),
        [](const std::vector<std::string>& a) -> int {
            if (a.size() < 3) {
                std::cout << H("Usage: neon remove <package>\n");
                return 0;
            }
            std::string pkgName = a[2];
            for (auto& pkg : packagesz) {
                if (pkg.name == pkgName && pkg.downloaded) {
                    std::cout << "Removing " << pkg.name << "...\n";
                    pkg.downloaded = false;
                    VNode* bin = resolvePath(H("/bin"));
                    if (bin) {
                        bin->children.erase(pkgName + H(".exc"));
                    }
                    progressbar(5);
                    std::cout << "Done!\n";
                    return 0;
                }
            }
            std::cout << H("No package with the name '") << pkgName << H("'\n");
            return 0;
        }
    };
    neonCommands[H("help")] = {
        H("help"),
        [](const std::vector<std::string>&) -> int {
            std::cout << H("neon package manager\ncommands:\n|install\n|remove\n|help\n|version\n");
            return 0;
        }
    };
    neonCommands[H("version")] = {
        H("version"),
        [](const std::vector<std::string>&) -> int {
            std::cout << H("N    N                             \n");
            std::cout << H("NN   N eeeee            (c)Nuebine \n");
            std::cout << H("N N  N e   e           Incorporated\n");
            std::cout << H("N  N N eeeee   NEON       Network  \n");
            std::cout << H("N   NN ee     PACKAGE      1998    \n");
            std::cout << H("N    N  eeee  MANAGER              \n");
            std::cout << H("               10.18               \n");
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