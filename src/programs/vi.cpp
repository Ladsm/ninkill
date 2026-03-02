#include <ui/userinput.hpp>
#include <vfs/vfs.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <numeric>
#if defined(_WIN32)
#define NOMINMAX
#include <conio.h>
#endif
#if defined(__linux__)
#include <unistd.h>
#include <termios.h>
#endif
#include <algorithm>
enum SpecialKeys {
    KEY_UP = 1001,
    KEY_DOWN = 1002,
    KEY_LEFT = 1003,
    KEY_RIGHT = 1004
};
#if defined(_WIN32)
static int readKeyVI() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int ch2 = _getch();
        switch (ch2) {
        case 72: return KEY_UP;
        case 80: return KEY_DOWN;
        case 75: return KEY_LEFT;
        case 77: return KEY_RIGHT;
        default: return 1000 + ch2;
        }
    }
    return ch;
}
#else
static int readKeyVI() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    if (ch == 27) {
        if (getchar() == '[') {
            switch (getchar()) {
            case 'A': ch = KEY_UP; break;
            case 'B': ch = KEY_DOWN; break;
            case 'D': ch = KEY_LEFT; break;
            case 'C': ch = KEY_RIGHT; break;
            default: ch = 27; break;
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void Vi(const std::vector<std::string>& args) {
    if (args.size() < 2) { std::cout << "Usage: vi <filename>\n"; return; }
    std::string filename = args[1];
    VNode* node = resolvePath(filename);
    std::vector<std::string> lines;
    if (node && !node->isDir) {
        std::stringstream ss(node->content);
        std::string s;
        while (std::getline(ss, s, '\n')) lines.push_back(s);
    }
    if (lines.empty()) lines.push_back("");
    int cursorLine = 0, cursorCol = 0;
    int scrollOffset = 0;
    const int screenHeight = 22;
    bool running = true;
    enum { COMMAND, INSERT } mode = COMMAND;
    while (running) {
        if (cursorLine < scrollOffset) scrollOffset = cursorLine;
        if (cursorLine >= scrollOffset + screenHeight) scrollOffset = cursorLine - screenHeight + 1;
        cursorCol = std::max(0, std::min(cursorCol, (int)lines[cursorLine].size()));
        std::cout << "\33[2J\33[H";
        for (int i = 0; i < screenHeight; ++i) {
            int idx = i + scrollOffset;
            if (idx < (int)lines.size()) {
                std::cout << "\33[33m" << (idx + 1) << " \33[0m" << lines[idx] << "\n";
            }
            else { std::cout << "~\n"; }
        }
        std::cout << "\33[24;1H\33[2K\33[7m "
            << (mode == INSERT ? "-- INSERT --" : "-- COMMAND --")
            << "  " << filename << " [" << (cursorLine + 1) << ":" << (cursorCol + 1) << "] \33[0m";
        std::cout << "\33[" << (cursorLine - scrollOffset + 1) << ";" << (cursorCol + 5) << "H" << std::flush;
        int key = readKeyVI();
        if (mode == COMMAND) {
            if (key == 'i') mode = INSERT;
            else if (key == ':') {
                std::cout << "\33[24;1H\33[2K:";
                std::string cmd; std::getline(std::cin, cmd);
                if (cmd == "q") running = false;
                else if (cmd == "w") {
                    std::string fullBody = "";
                    for (const auto& l : lines) fullBody += l + "\n";
                    if (node) node->content = fullBody;
                    else node = mkfile(cwd, filename, fullBody);
                }
            }
            else if (key == KEY_UP && cursorLine > 0) {
                cursorLine--;
            }
            else if (key == KEY_DOWN && cursorLine < (int)lines.size() - 1) {
                cursorLine++;
            }
            else if (key == KEY_LEFT && cursorCol > 0) {
                cursorCol--;
            }
            else if (key == KEY_RIGHT && cursorCol < (int)lines[cursorLine].size()) {
                cursorCol++;
            }
        }
        else if (mode == INSERT) {
            if (key == 27) mode = COMMAND;
            else if (key == 8 || key == 127) {
                if (cursorCol > 0) {
                    lines[cursorLine].erase(cursorCol - 1, 1);
                    cursorCol--;
                }
                else if (cursorLine > 0) {
                    cursorCol = lines[cursorLine - 1].size();
                    lines[cursorLine - 1] += lines[cursorLine];
                    lines.erase(lines.begin() + cursorLine);
                    cursorLine--;
                }
            }
            else if (key == '\r' || key == '\n') {
                std::string remainder = lines[cursorLine].substr(cursorCol);
                lines[cursorLine] = lines[cursorLine].substr(0, cursorCol);
                lines.insert(lines.begin() + cursorLine + 1, remainder);
                cursorLine++;
                cursorCol = 0;
            }
            else if (key >= 32 && key <= 126) {
                lines[cursorLine].insert(cursorCol, 1, (char)key);
                cursorCol++;
            }
        }
    }
    std::cout << "\33[2J\33[H";
}