#include <util/obfstr.hpp>
#include <util/getwh.hpp>
#include <ui/menu.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#if defined(_WIN32)
#include <conio.h>
#endif
#if defined(__linux__)
#include <unistd.h>
#include <termios.h>
int getch() {
    struct termios old_settings, new_settings;
    int ch;
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}
#endif
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
#if defined(_WIN32)
    int selected = 1;
    int keypressed = 0;
    while (true) {
        DisplayMenu(ItemsToUse, selected, amountofItems, H("NIN BOOT MANAGER"));
        keypressed = _getch();
        if (keypressed == 'x' || keypressed == 'X') {
            std::exit(0);
        }
        if (keypressed == 0 || keypressed == 0xE0) {
            keypressed = _getch();
            switch (keypressed) {
            case 72: // up
                if (selected > 1) {
                    selected--;
                }
                break;
            case 80: // down
                if (selected < amountofItems) {
                    selected++;
                }
                break;
            }
        }
        else {
            if (keypressed == '\r') {
                int idx = selected - 1;
                if (idx >= 0 && idx < static_cast<int>(callbacks.size()) && callbacks[idx]) {
                    callbacks[idx]();
                }
                return;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
#elif defined(__linux__)
    int selected = 1;

    while (true) {
        DisplayMenu(ItemsToUse, selected, amountofItems, H("NIN BOOT MANAGER"));
        int ch = getch();
        if (ch == 'x' || ch == 'X')
            std::exit(0);
        if (ch == 27) {
            int c2 = getch();
            if (c2 == '[') {
                int c3 = getch();
                switch (c3) {
                case 'A':
                    if (selected > 1) selected--;
                    break;
                case 'B':
                    if (selected < amountofItems) selected++;
                    break;
                }
            }
        }
        else if (ch == 10 || ch == 13) {
            int idx = selected - 1;
            if (idx >= 0 && idx < (int)callbacks.size() && callbacks[idx])
                callbacks[idx]();
            return;
        }
    }
#endif
}
