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
    std::cout << "\033[2J";
    std::cout << "\033[H";
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    int innerWidth = width - 2;
    std::cout << "\033[97;44m";
    std::cout << "+" << std::string(innerWidth, '-') << "+\n";
    std::string titleText = " " + title;
    std::string closeButton = "[X]";
    int spacing = innerWidth - titleText.length() - closeButton.length();
    if (spacing < 1) spacing = 1;
    std::cout << "|"<< titleText<< std::string(spacing, ' ')<< closeButton<< "|\n";
    std::cout << "+" << std::string(innerWidth, '-') << "+\n";
    std:: cout << "\033[48;2;192;192;192m";
    std:: cout << "\033[38;2;0;0;0m";
    int contentHeight = amountofItems;
    int topPadding = (height - contentHeight - 4) / 2;
    if (topPadding < 0) topPadding = 0;
    for (int i = 0; i < topPadding; ++i)
        std::cout << "|" << std::string(innerWidth, ' ') << "|\n";
    for (int i = 0; i < amountofItems; ++i) {
        std::string prefix = ((i + 1) == WhatsSelected) ? "-> " : "   ";
        std::string text = prefix + ItemsToShow[i];
        int paddingLeft = (innerWidth - text.length()) / 2;
        if (paddingLeft < 0) paddingLeft = 0;
        int paddingRight = innerWidth - paddingLeft - text.length();
        if (paddingRight < 0) paddingRight = 0;
        std::cout << "|" << std::string(paddingLeft, ' ') << text << std::string(paddingRight, ' ') << "|\n";
    }
    int usedHeight = topPadding + contentHeight;
    int bottomPadding = height - usedHeight - 4;
    if (bottomPadding < 0) bottomPadding = 0;
    for (int i = 0; i < bottomPadding; ++i)
        std::cout << "|" << std::string(innerWidth, ' ') << "|\n";
    std::cout << "+" << std::string(innerWidth, '-') << "+";
    std::cout << "\033[0m";
    std::cout.flush();
}
void MenuUse(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems) {
#if defined(_WIN32)
    int selected = 1;
    int keypressed = 0;
    while (true) {
        DisplayMenu(ItemsToUse, selected, amountofItems, "BOOT MANAGER");
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
        DisplayMenu(ItemsToUse, selected, amountofItems, "BOOT MANAGER");
        int ch = getch();
        if (ch == 'x' || ch == 'X') {
            std::exit(0);
        }
        switch (ch) {
        case 65:
            selected--;
            break;
        case 66:
            selected++;
            break;
        case 10:
            int idx = selected - 1;
            if (idx >= 0 && idx < static_cast<int>(callbacks.size()) && callbacks[idx]) {
                callbacks[idx]();
            }
            return;
        }
    }
#endif
}
void cls() {
	std::cout << "\033[2J\033[H";
}
void openOS() {
    std::cout << "\033[2J\033[H";
    std::cout << "Booting NINKILL OS 1.3 "; threedot(); std::cout << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cls();
}
void backToBIOS() {
    std::cout << "\033[2J\033[H";
    std::cout << "Returning to BIOS "; threedot(); std::cout << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cls();
    std::exit(0);
}
void showBootMenu() {
    std::string items[] = {
        "NINKILL OS 1.3",
        "Back to BIOS"
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
	std::cout << "\033[?25l";
	std::cout.flush();
}
static void moveCursorTop() {
    std::cout << "\033[H";
}
void bootanim() {
    ensureConsoleInitialized();
    std::vector<std::pair<std::string, std::string>> logo = {
        {"NN    NN ", "II NN    NN  KK  KK II LL       LL      "},
        {"NNNN  NN ", "II NNNN  NN  KK KK  II LL       LL      "},
        {"NN NN NN ", "II NN NN NN  KKKK   II LL       LL  OS  "},
        {"NN  NNNN ", "II NN  NNNN  KK KK  II LL       LL      "},
        {"NN   NNN ", "II NN   NNN  KK  KK II LLLLLLLL LLLLLLLL"}
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
        std::cout << "\033[H";
        for (int k = 0; k < topPadding; k++) std::cout << "\n";
        for (auto& [fixed, moving] : logo) {
            std::string current = fixed;
            if (i <= moving.size()) current += moving.substr(0, i);
            else current += moving;
            Center() << current;
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    Center() << "\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Center() << "Nuebine Incorperated Network operating system";
    Center() << "Version 1.3";
    Center() << "\n\n\n\n\n\n";
    blop(700, 400);
    blop(1500, 300);
    blop(300, 400);
    blop(500, 100);
    blop(700, 100);
    blop(1000, 100);
    blop(2000, 1000);
    blop(300, 100);
    Center() << "(c)Nuebine Incorperated Network, 1998. All Rights Reserved";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}