#include <util/obfstr.hpp>
#include <util/term/getwh.hpp>
#include <ui/spiner.hpp>
#include <ui/center.hpp>
#include <net/website.hpp>
#include <ui/userinput.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

void clscls() {
    std::cout << H("\033[2J\033[H");
}
void connecting(const std::string& address, bool fail) {
    mkbg();
    loadingSpinnerCentered(800, H("Connecting to ") + address + ' ');
    mkbg();
    if (fail)
    {
        Center() << H("404 - No website at that address");
        Center() << H("Are you sure the website is using the spp internet maker?");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    loadingSpinnerCentered(800, H("Resolving host... "));
    mkbg();
    loadingSpinnerCentered(100, H("Connected."));
}
void drawBox(std::string text) {
    Center() << H("+----------------------------------------+");
    Center() << (SAFESTR("| ") + text + std::string(38 - text.size(), ' ') + H(" |"));
    Center() << H("+----------------------------------------+");
    };
void internet() {
    auto routes = buildRouter();
    std::string site;
    loadingSpinnerCentered(1000, H("Loading"));
    loadingSpinnerCentered(3000, H("Connecting"));
    while (true) {
        site.clear();
        while (true) {
            mkbg();
            Center() << H("Network Internet Navigator");
            Center() << H("Enter Internet address (or type 'exit'):");
            drawBox(site);
            int ch = readKey();
            if (ch == '\r' || ch == '\n') {
                if (site.empty())
                    continue;
                break;
            }
            else if ((ch == 8 || ch == 127) && !site.empty())
                site.pop_back();
            else if (ch >= 32 && ch <= 126 && site.size() < 38)
                site.push_back((char)ch);
        }
        std::transform(site.begin(), site.end(), site.begin(), ::tolower);
        if (site == H("exit")) {
            std::cout << H("\033[32;40m");
            return;
        }
        auto it = routes.find(site);
        if (it == routes.end()) {
            connecting(site, true);
            continue;
        }
        connecting(site, false);
        it->second();
    }
}