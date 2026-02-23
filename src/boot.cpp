#include "boot.hpp"
#include "beep.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#if defined(_WIN32)
#include <windows.h>
#endif

void threedot(){
	for (int i = 0; i < 3; i++) {
		std::cout << '.';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return;
}
void cls() {
	std::cout << "\033[2J\033[H";
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