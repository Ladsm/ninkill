#include <util/obfstr.hpp>
#include <util/getwh.hpp>
#include <ui/spiner.hpp>
#include <ui/center.hpp>
#include <net/website.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

int isAddress(const std::string& address) {
    if (address == H("www.Nuebine.com") || address == H("www.nuebine.com"))
        return 1;
    else if (address.empty())
        return 2;
    else if (address == H("exit"))
        return 3;
    else if (address == H("www.jackwd.com"))
        return 4;
    return 0;
}
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
void internet() {
    auto routes = buildRouter();
    std::string site;
    loadingSpinnerCentered(1000, H("Loading"));
    loadingSpinnerCentered(3000, H("Connecting"));
    while (true) {
        clscls();
        mkbg();
        Center() << H("Network Internet Navigator");
        Center() << H("Enter Internet address (or type 'exit'):");
        std::cout << std::string(getConsoleWidth() / 2 - 15, ' ');
        std::getline(std::cin >> std::ws, site);
        if (site.empty())
            continue;
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