#include <util/obfstr.hpp>
#include <util/term/getwh.hpp>
#include <ui/menu.hpp>
#include <ui/userinput.hpp>
#include <boot/bootcli.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>

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