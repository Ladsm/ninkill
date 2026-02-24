#include "website.hpp"
#include "ninkill.hpp"
#include <iostream>
void printgrayeBar(int row) {
    int width = getConsoleWidth();
    std::cout << "\033[1;1H";
    std::cout << "\033[100;97m";
    std::cout << std::string(width, ' ');
    std::cout << "\033[44;97m";
    std::cout << "\033[2;1H";
}
void mkbg() {
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    std::cout << "\033[97;44m";
    std::cout << "\033[H";
    for (int y = 0; y < height; y++) {
        std::cout << std::string(width, ' ');
    }
    printgrayeBar(1);
    std::cout << "\033[H";
    std::cout << "\033[2;1H";
}
void wwwNuebinedotcom() {
    int choice;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            std::cout << "Welcome to Nuebine Incorporated!\n";
            std::cout << "Innovating the Network Since 1990\n";
            std::cout << "[1] About\n";
            std::cout << "[2] Projects\n";
            std::cout << "[3] Exit\n";
            std::cin >> choice;
            if (choice == 1) {
                page = 2;
            }
            else if (choice == 2) {
                page = 3;
            }
            else if (choice == 3) {
                return;
            }
            else {
                std::cout << "Not an option\n";
            }
            break;
        case 2:
            std::cout << "About Nuebine:\nWe make all things tech, software, hardware and more...\nWe started in 1990 in Washington and over the years, we have goten larger and larger, from a two man team, to over fifty employees.\n";
            std::cout << "[1] Back\n";
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << "Not an option\n";
            }
            break;
        case 3:
            std::cout << "Our projects:\n - NINKILL os\nNINKILL os is a small linux based operating system made for home users, load it with a flopy drive like a DOS\n";
            std::cout << " - NINKILL forums\nThe forums are an acsessable way for people to talk online, no portforwarding or weird manual installs. Just load it up and enter the chat\n";
            std::cout << " - NINKILL internet Navigator\nA way to see things in a without needing to download it, just some temperary files and when you finish using the content, the files get deleted\n";
            std::cout << "[1] Back\n";
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << "Not an option\n";
            }
            break;
        }
    }
}
website Nuebinedotcom = website("www.Nuebine.com", wwwNuebinedotcom);