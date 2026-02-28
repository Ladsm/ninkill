#include "obfstr.hpp"
#include "boot.hpp"
#include "ninkill.hpp"
#include "beep.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
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
void threedot();
void ensureConsoleInitialized();
void DisplayMenu(std::string ItemsToShow[],int WhatsSelected,int amountofItems,const std::string& title) {
    ensureConsoleInitialized();
    std::cout << H("\033[2J");
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
    int spacing = innerWidth - titleText.length() - closeButton.length() - fullButton.length() - minButton.length();
    spacing += 4;
    if (spacing < 1) spacing = 1;
    std::cout << H("|")<< titleText<< std::string(spacing, ' ')<< minButton << fullButton << closeButton<< H("|\n");
    std::cout << H("+") << std::string(innerWidth, '-') << H("+\n");
    std:: cout << H("\033[48;2;192;192;192m");
    std:: cout << H("\033[38;2;0;0;0m");
    int contentHeight = amountofItems;
    int topPadding = (height - contentHeight - 4) / 2;
    if (topPadding < 0) topPadding = 0;
    for (int i = 0; i < topPadding; ++i)
        std::cout << H("|") << std::string(innerWidth, ' ') << H("|\n");
    for (int i = 0; i < amountofItems; ++i) {
        std::string prefix = ((i + 1) == WhatsSelected) ? H("-> ") : H("   ");
        std::string text = prefix + ItemsToShow[i];
        int paddingLeft = (innerWidth - text.length()) / 2;
        if (paddingLeft < 0) paddingLeft = 0;
        int paddingRight = innerWidth - paddingLeft - text.length();
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
void cls() {
	std::cout << H("\033[2J\033[H");
}
void openOS() {
    std::cout << H("\033[2J\033[H");
    std::cout << SAFESTR("Booting NINKILL OS 1.3 "); threedot();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
void backToBIOS() {
    std::cout << H("\033[2J\033[H");
    std::cout << H("Returning to BIOS "); threedot(); std::cout << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cls();
    std::exit(0);
}
void showBootMenu() {
    std::string items[] = {
        H("NINKILL OS 1.3"),
        H("Back to BIOS")
    };
    std::vector<std::function<void()>> actions = {
        openOS,
        backToBIOS
    };
    std::this_thread::sleep_for(std::chrono::seconds(1));
    MenuUse(items, actions, 2);
}
void threedot(){
	for (int i = 0; i < 3; i++) {
		std::cout << '.';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return;
}
void ensureConsoleInitialized() {
	static bool initialized = false;
	if (initialized) return;
	initialized = true;
#if defined(_WIN32)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut != INVALID_HANDLE_VALUE) {
		DWORD mode = 0;
		if (GetConsoleMode(hOut, &mode)) {
			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOut, mode);
		}
	}
#endif
	std::cout << SAFESTR("\033[?25l");
	std::cout.flush();
}
static void moveCursorTop() {
    std::cout << H("\033[H");
}
void bootanim() {
    ensureConsoleInitialized();
    std::vector<std::pair<std::string, std::string>> logo = {
        {H("NN    NN "), H("II NN    NN  KK  KK II LL       LL      ")},
        {H("NNNN  NN "), H("II NNNN  NN  KK KK  II LL       LL      ")},
        {H("NN NN NN "), H("II NN NN NN  KKKK   II LL       LL  OS  ")},
        {H("NN  NNNN "), H("II NN  NNNN  KK KK  II LL       LL      ")},
        {H("NN   NNN "), H("II NN   NNN  KK  KK II LLLLLLLL LLLLLLLL")}
    };
    int consoleHeight = 25;
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) consoleHeight = w.ws_row;
#endif
    int topPadding = (consoleHeight - static_cast<int>(logo.size())) / 2;
    size_t maxLen = 0;
    for (auto& [fixed, moving] : logo)
        if (moving.size() > maxLen) maxLen = moving.size();
    for (size_t i = 0; i <= maxLen; i++) {
        std::cout << H("\033[H");
        for (int k = 0; k < topPadding; k++) std::cout << H("\n");
        for (auto& [fixed, moving] : logo) {
            std::string current = fixed;
            if (i <= moving.size()) current += moving.substr(0, i);
            else current += moving;
            Center() << current;
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    Center() << H("\n\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Center() << H("Nuebine Incorperated Network operating system");
    Center() << H("Version 1.3");
    Center() << H("\n\n\n\n\n\n");
    blop(700, 400);
    blop(1500, 300);
    blop(300, 400);
    blop(500, 100);
    blop(700, 100);
    blop(1000, 100);
    blop(2000, 1000);
    blop(300, 100);
    Center() << SAFESTR("(c)Nuebine Incorperated Network, 1998. All Rights Reserved");
    std::this_thread::sleep_for(std::chrono::seconds(3));
}