#pragma once
#include <util/obfstr.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#include <WinBase.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
void threedot();
void cls();
void bootanim();
void ensureConsoleInitialized();
void showBootMenu();
class Center {
public:
    static int getWidth() {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) return w.ws_col;
#endif
        return 80;
    }
    struct Proxy {
        std::stringstream buffer;
        Proxy() = default;
        Proxy(Proxy&& other) noexcept : buffer(std::move(other.buffer)) {}
        Proxy(const Proxy&) = delete;
        int visibleLength(const std::string& s) {
            int len = 0;
            bool in_code = false;
            for (size_t i = 0; i < s.length(); ++i) {
                if (s[i] == '\033') { in_code = true; continue; }
                if (in_code) {
                    if (s[i] == 'm') in_code = false;
                    continue;
                }
                if ((static_cast<unsigned char>(s[i]) & 0xC0) != 0x80) {
                    len++;
                }
            }
            return len;
        }
        template<typename T>
        Proxy& operator<<(const T& val) {
            buffer << val;
            return *this;
        }
        ~Proxy() {
            std::string s = buffer.str();
            if (s.empty()) return;
            bool hasCarriageReturn = (!s.empty() && s.back() == '\r');
            if (hasCarriageReturn) {
                s.pop_back();
            }
            int width = getWidth();
            int padding = (width - visibleLength(s)) / 2;
            if (padding > 0) std::cout << std::string(padding, ' ');
            std::cout << s;
            if (hasCarriageReturn) {
                std::cout << H("\r") << std::flush;
            }
            else {
                std::cout << std::endl;
            }
        }
    };
    template<typename T>
    Proxy operator<<(const T& val) {
        Proxy p;
        p << val;
        return std::move(p);
    }
};