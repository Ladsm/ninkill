#include <util/obfstr.hpp>
#include <util/term/getwh.hpp>
#include <ui/menu.hpp>
#include <ui/userinput.hpp>
#include <system/storage/savefile.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <fstream>
#include <filesystem>
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
int bootcli() {
    bool canboot = true;
    std::cout << H("\033[2J\033[H");
    std::cout << H("The NuebinebootShell is system utility to recover lost systems\nWrite \'help\' for more info\n");
    while (true) {
        if (canboot == false) {
            makefile();
        }
        std::cout << "NueBootSH> " << std::flush;
        std::string command = getcommandBoot();
        if (command == "help") {
            std::cout << H("sorry, no help page yet\n");
        }
        else if (command == "boot") {
            if (canboot == true) {
                return 1;
            }
            else {
                std::cout << H("No bootable device found\n");
            }
        }
        else if (command == "bios"||command == "exit") {
            std::exit(0);
        }
        else if (command == "ls" || command == "dir") {
            if (canboot == true) {
                std::cout << "ninkill.exc\n";
                std::cout << "h.txt\n";
            }
        }
        else if (command == "mkfs hda" || "mkfs fd0") {
            std::cout << "formated device\n";
            canboot = false;
        }
        else if (command == "h"||command == "cat h.txt") {
            std::cout << H("Hello, Hoien Shaun Dow here.\n");
            std::cout << H("I programed the Nuebine Boot Shell utility.\n");
            std::cout << H("The Nue boot is vary weird(this is why you dont program important software at 3am).\n");
            std::cout << H("It first loads the kernel's inerd but then insted of loading the full kernel and then the init script,\n");
            std::cout << H("it insted only loads the init script and while it runs it loads the kernel but only the things the init script needs\nOnly after that it load the kernel\n");
            std::cout << H("The start animation is only thare because it took too long to start the kernel, so I programed it to run while the kernel is booting\n3 am majic I geess\n");
        }
        else if (command == "pwd") {
            std::cout << "/\n";
        }
        else if (command == "lsblk") {
            std::cout << H("NAME  SIZE   TYPE \n");
            std::cout << H("----------------- \n");
            std::cout << H("hda  5.05GB  disk \n");
            std::cout << H("fd0  10.3MB  flopy\n");
        }
        else if (command == "mkfs") {
            std::cout << H("makeing file system at all devices with format mfs\n");
            canboot = false;
        }
        else {
            std::cout << "unknown command " << command << '\n';
        }
    }
}
void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, const std::string& title) {
    std::cout << SAFESTR("\033[H");
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    int innerWidth = width - 2;
    std::cout << H("\033[97;44m");
    std::cout << H("+") << std::string(innerWidth, '-') << H("+\n");
    std::string titleText = H(" ") + title;
    std::string closeButton = H("[╳]");
    std::string fullButton = H("[O]");
    std::string minButton = H("[─]");
    size_t spacing = innerWidth - titleText.length() - closeButton.length() - fullButton.length() - minButton.length();
    spacing += 4;
    if (spacing < 1) spacing = 1;
    std::cout << H("|") << titleText << std::string(spacing, ' ') << minButton << fullButton << closeButton << H("|\n");
    std::cout << H("+") << std::string(innerWidth, '-') << H("+\n");
    std::cout << H("\033[48;2;192;192;192m");
    std::cout << H("\033[38;2;0;0;0m");
    int contentHeight = amountofItems;
    int topPadding = (height - contentHeight - 4) / 2;
    if (topPadding < 0) topPadding = 0;
    for (int i = 0; i < topPadding; ++i)
        std::cout << H("|") << std::string(innerWidth, ' ') << H("|\n");
    for (int i = 0; i < amountofItems; ++i) {
        std::string prefix = ((i + 1) == WhatsSelected) ? H("-> ") : H("   ");
        std::string text = prefix + ItemsToShow[i];
        size_t paddingLeft = (innerWidth - text.length()) / 2;
        if (paddingLeft < 0) paddingLeft = 0;
        size_t paddingRight = innerWidth - paddingLeft - text.length();
        if (paddingRight < 0) paddingRight = 0;
        std::cout << H("|") << std::string(paddingLeft, ' ') << text << std::string(paddingRight, ' ') << H("|\n");
    }
    int usedHeight = topPadding + contentHeight;
    int bottomPadding = height - usedHeight - 4;
    if (bottomPadding < 0) bottomPadding = 0;
    for (int i = 0; i < bottomPadding; ++i)
        std::cout << SAFESTR("|") << std::string(innerWidth, ' ') << H("|\n");
    std::cout << H("+") << std::string(innerWidth, '-') << H("+");
    std::cout << H("\033[0m");
    std::cout.flush();
}
void MenuUse(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems) {
    int selected = 1;
    int toboot = 0;
    while (true) {
        DisplayMenu(ItemsToUse, selected, amountofItems, H("NIN BOOT MANAGER"));
        InputType input = GetPlayerInput();
        if (input == InputType::MoveUp && selected > 1) {
            selected--;
        }
        else if (input == InputType::MoveDown && selected < amountofItems) {
            selected++;
        }
        else if (input == InputType::Enter) {
            int idx = selected - 1;
            if (idx >= 0 && idx < (int)callbacks.size() && callbacks[idx]) callbacks[idx]();
            return;
        }
        else if (input == InputType::E) {
            toboot = bootcli();
            if (toboot == 1) {
                selected = 1;
                return;
            }
            else {
                selected = 2;
                return;
            }
        }
        else if (input == InputType::Escape) {
            std::exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}