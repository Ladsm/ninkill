#include <util/obfstr.hpp>
#include <util/text/longtexts.h>
#include <system/storage/savefile.hpp>
#include <ui/userinput.hpp>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <map>

namespace fs = std::filesystem;
void makefile() {
    std::string baseDir = getAppDataPath();
    if (baseDir.empty()) return;
    fs::path filePath = fs::path(baseDir) / "bricked.bin";
    try {
        if (filePath.has_parent_path()) {
            fs::create_directories(filePath.parent_path());
        }

        std::ofstream outfile(filePath, std::ios::binary);
        if (outfile.is_open()) {
            outfile << "Bricked lol";
            outfile.close();
        }
    }
    catch (const std::exception& e) {
    }
}
bool checkfile() {
    std::string baseDir = getAppDataPath();
    if (baseDir.empty()) return false;

    fs::path filePath = fs::path(baseDir) / "bricked.bin";
    return fs::exists(filePath);
}
std::string getcommandBoot() {
    static std::vector<std::string> history;
    int historyIndex = history.size();
    std::string buf;
    size_t cursor = 0;
    const std::string prompt = H("NueBootSH> ");
    auto redraw = [&]() {
        std::cout << H("\33[2K\r") << prompt << buf;
        std::cout << H("\r\33[") << (cursor + prompt.size()) << H("C") << std::flush;
        };
    while (true) {
        int key = readKey();
        if (key == '\n' || key == '\r') {
            std::cout << H("\n");
            if (!buf.empty())
                history.push_back(buf);
            return buf;
        }
        else if (key == 8 || key == 127) {
            if (cursor > 0) {
                buf.erase(cursor - 1, 1);
                cursor--;
                redraw();
            }
        }
        else if (key == 1000 + 83 || key == 1000 + '3') {
            if (cursor < buf.size()) {
                buf.erase(cursor, 1);
                redraw();
            }
        }
        else if (key == 1000 + 75 || key == 1000 + 'D') {
            if (cursor > 0) {
                cursor--;
                redraw();
            }
        }
        else if (key == 1000 + 77 || key == 1000 + 'C') {
            if (cursor < buf.size()) {
                cursor++;
                redraw();
            }
        }
        else if (key == 1000 + 72 || key == 1000 + 'A') {
            if (historyIndex > 0) {
                historyIndex--;
                buf = history[historyIndex];
                cursor = buf.size();
                redraw();
            }
        }
        else if (key == 1000 + 80 || key == 1000 + 'B') {
            if (historyIndex < (int)history.size() - 1) {
                historyIndex++;
                buf = history[historyIndex];
            }
            else {
                historyIndex = history.size();
                buf.clear();
            }
            cursor = buf.size();
            redraw();
        }
        else if (key >= 32 && key <= 126) {
            buf.insert(cursor, 1, (char)key);
            cursor++;
            redraw();
        }
    }
}
using CommandMap = std::map<std::string, std::function<void(std::vector<std::string>)>>;
static CommandMap bootCommands;
static bool canBoot = true;
static bool shouldExit = false;
static int bootResult = 0;
void initCommands() {
    bootCommands = CommandMap{
        {"help", [](auto args) { std::cout << H("sorry, no help page yet\n"); }},
        {"boot", [](auto args) {
            if (canBoot) { bootResult = 1; shouldExit = true; }
            else { std::cout << H("No bootable device found\n"); }
        }},
        {"bios", [](auto args) { std::exit(0); }},
        {"exit", [](auto args) { std::exit(0); }},
        {"ls",   [](auto args) { if (canBoot) std::cout << "ninkill.exc\nh.txt\n"; }},
        {"dir",  [](auto args) { if (canBoot) std::cout << "ninkill.exc\nh.txt\n"; }},
        {"pwd",  [](auto args) { std::cout << "/\n"; }},
        {"lsblk",[](auto args) { std::cout << H("NAME SIZE TYPE \n----------------- \nhda 5.05GB disk \nfd0 10.3MB flopy\n"); }},
        {"mkfs", [](auto args) { std::cout << H("formated device\n"); makefile(); canBoot = false; }},
        {"cat", [&](auto args) {
            if (args.empty()) {
                std::cout << H("Usage: cat <filename>\n");
                return;
            }
            if (args[0] == "h.txt") {
                std::cout << H("Hello, Hoien Shaun Dow here.\n");
                std::cout << H("I programed the Nuebine Boot Shell utility.\n");
                std::cout << H("The Nue boot is vary weird(this is why you dont program important software at 3am).\n");
                std::cout << H("it insted only loads the init script and while it runs it loads the kernel but only the things the init script needs\nOnly after that it load the kernel\n");
                std::cout << H("The start animation is only thare because it took too long to start the kernel, so I programed it to run while the kernel is booting\n3 am majic I geess\n");
            }
            else if (args[0] == "ninkill.exc") {
                std::cout << H("Hello, Hoien Shaun Dow here.\n") << H("This is just the linux kernel, check: www.hoiendow.net/linux to know more about what I think about this\n") << gibernelf() << "\nMNFSTO-PAS:*NIN*LINUX*FREE\n" << gibernelf();
            } 
            else {
                std::cout << H("cat: ") << args[0] << H(": No such file or directory\n");
            }
        }},
        {"h",    [](auto args) {
                    std::cout << H("Hello, Hoien Shaun Dow here.\n");
                    std::cout << H("I programed the Nuebine Boot Shell utility.\n");
                    std::cout << H("The Nue boot is vary weird(this is why you dont program important software at 3am).\n");
                    std::cout << H("it insted only loads the init script and while it runs it loads the kernel but only the things the init script needs\nOnly after that it load the kernel\n");
                    std::cout << H("The start animation is only thare because it took too long to start the kernel, so I programed it to run while the kernel is booting\n3 am majic I geess\n");
        }},
        {"whoami", [](auto args) { std::cout << H("NueRootBoot\n"); }},
        {"recover", [](auto args) {
            std::cout << H("Starting");
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".\n";
            std::cout << "Makeing filesystems";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".\n";
            std::cout << "Etching image to disks";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".\n";
            std::cout << "Exiting recovery";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << ".\n";
        }}
    };
    bootCommands["mkfs hda"] = bootCommands["mkfs"];
    bootCommands["mkfs fd0"] = bootCommands["mkfs"];
    bootCommands["ninkill.exc"] = bootCommands["boot"];
}

void processCommand(const std::string& input) {
    if (input.empty()) return;
    std::stringstream ss(input);
    std::string cmd;
    ss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (ss >> arg) args.push_back(arg);
    auto it = bootCommands.find(cmd);
    if (it != bootCommands.end()) {
        it->second(args);
    }
    else {
        std::cout << "unknown command " << cmd << '\n';
    }
}

int bootcli() {
    initCommands();
    shouldExit = false;
    std::cout << H("\033[2J\033[HThe NuebinebootShell is system utility made to recover lost systems\n");
    while (!shouldExit) {
        std::cout << "NueBootSH> " << std::flush;
        processCommand(getcommandBoot());
    }
    return bootResult;
}