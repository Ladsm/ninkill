#include <util/obfstr.hpp>
#include <boot/boot.hpp>
#include <net/ninkill.hpp>
#include <util/beep.h>
#include <ui/menu.hpp>
#include <ui/center.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#if defined(_WIN32)
#include <conio.h>
#include <Windows.h>
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