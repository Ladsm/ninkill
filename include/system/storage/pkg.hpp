#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
struct NeonCommand {
    std::string name;
    std::function<int(const std::vector<std::string>&)> action;
};
struct package {
public:
    std::string name = "pkgname";
    std::string message = "download message";
    bool willDownload = false;
    bool downloaded = false;
    bool hidden = false;
    package(std::string a, std::string b, bool c, bool d)
        : name(a), message(b), willDownload(c), downloaded(d) {
    }
    package(std::string a, std::string b, bool c, bool d, bool e)
        : name(a), message(b), willDownload(c), downloaded(d) , hidden(e){
    }
    package() = default;
};
extern const std::vector<std::string> ninfetch;
extern std::unordered_map<std::string, NeonCommand> neonCommands;
extern std::vector<package> packagesz;
void initNeon();
int neon_cmd(const std::vector<std::string>& args);
void installPackage(package* pkg);
void removePackage(package* pkg);