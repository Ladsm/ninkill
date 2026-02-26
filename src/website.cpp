#include "obfstr.hpp"
#include "website.hpp"
#include "ninkill.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>
void printgrayeBar(int row) {
    int width = getConsoleWidth();
    std::cout << H("\033[1;1H");
    std::cout << H("\033[100;97m");
    std::cout << std::string(width, ' ');
    std::cout << H("\033[44;97m");
    std::cout << H("\033[2;1H");
}
void mkbg() {
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    std::cout << H("\033[97;44m");
    std::cout << H("\033[H");
    for (int y = 0; y < height; y++) {
        std::cout << std::string(width, ' ');
    }
    printgrayeBar(1);
    std::cout << H("\033[H");
    std::cout << H("\033[2;1H");
}
void wwwNuebinedotcom() {
    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            std::cout << H("Welcome to Nuebine Incorporated!\n");
            std::cout << H("Innovating the Network Since 1990\n");
            std::cout << H("[1] About\n");
            std::cout << H("[2] Projects\n");
            std::cout << H("[3] Exit\n");
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
                std::cout << H("Not an option\n");
            }
            break;
        case 2:
            std::cout << H("About Nuebine:\nWe make all things tech—software, hardware, and more...\nWe started in 1990 in Washington, and over the years we have grown larger and larger, from a two-man team to over fifty employees.\n");
            std::cout << H("[1] Back\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        case 3:
            std::cout << H("Our projects:\n - NINKILL OS\nNINKILL OS is a small Linux-based operating system made for home users. Load it with a floppy drive like DOS.\n");
            std::cout << H(" - NINKILL Forums\nThe forums are an accessible way for people to talk online—no port forwarding or weird manual installs. Just load it up and enter the chat.\n");
            std::cout << H(" - NINKILL Internet Navigator\nA way to see things without needing to download them—just some temporary files, and when you finish using the content, the files get deleted.\n");
            std::cout << H("[1] Back\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        }
    }
}
void wwwJackwddotcom() {
    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            std::cout << H("Hello, im Jack Wilder Dean. Im a software engineer based in Texes, I made this website and the internet explorer you're in.\n");
            std::cout << H("[1] Portfolio\n[2] Nuebine's theft and hire\n[3] Exit\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 2;
            }
            if (choice == 2) {
                page = 3;
            }
            if (choice == 3) {
                return;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        case 2:
            std::cout << H("My portfolio:\n - Internet Explorer\nThis is a piece of software I made that temporarily downloads files from a server, then after 10 minutes the files get wiped from your computer.\n");
            std::cout << H("To protect from ACE, it uses a proxy server. This is a diagram of how it works:\n");
   std::cout << STATIC_DEF("                    .-----.         .-----------.    ") << '\n';
            std::cout << H("   .----.     Fire  |  P  |         |   Server  + - +") << '\n';
            std::cout << H("   |$>_ | - - - - - |  R  |         `-----+-----'   |") << '\n';
            std::cout << H(" __|____|__   Wall  |  O  | - - - - - - - |         |") << '\n';
            std::cout << H("|PC______--|        |  X  |         .-----+-----.   |") << '\n';
           std::cout << H("`-/.::::.\\-'      +-+  Y  +-+       |  Display  |   |") << '\n';
            std::cout << H(" `--------'       | `-----' |       `-----+-----'   |") << '\n';
            std::cout << H("      |           |         |             |         |") << '\n';
            std::cout << H("      + - - - - - +         + - - - - - - + - - - - +") << '\n';
   std::cout << STATIC_DEF("Software Employment:\n1990–1997 - Jack's Software Products\n1997–now - Head Software Engineer at Nuebine Incorporated Network\n");
            std::cout << H("[1] Back\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        case 3:
            std::cout << H("You may have come here due to a legal notice you found in Nuebine's Network Internet Navigator.\n");
            std::cout << H("This all started after I made Internet Explorer in 1997. It was a piece of software I liked a lot.\nBut after two months, Nuebine made a new product named \"Network Internet Navigator\". It looked the same as my software, just with some extra Nuebine stuff.\n");
            std::cout << H("I contacted them and they lied to me. They told me they started working on it in 1996 and that I was making a false claim.\n");
            std::cout << H("I know they lied because the proxy servers were getting requests from Nuebine.co.us.\n");
            std::cout << H("I filed a legal notice demanding they show me their code. At first they told me no, but then decided to let me come in.\n");
            std::cout << STATIC_DEF("On that day I went into their office. After I saw my code on their computers, I told them I demanded a cut of the profit.\n");
            std::cout << H("And you know what? They agreed. They told me it was fine and let me get a job. (My self-employed ass took this as fast as I could.)\n");
            std::cout << H("I now work as the head software engineer with them.\nMoral of the story: Don’t steal.\n");
            std::cout << H("[1] Back\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 1;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        }
    }
}
using RouteTable = std::unordered_map<std::string, std::function<void()>>;
RouteTable buildRouter() {
    return {
        {H("www.nuebine.com"), wwwNuebinedotcom},
        {H("www.Nuebine.com"), wwwNuebinedotcom},
        {H("Nuebine.co.us"), wwwNuebinedotcom },
        {H("www.jackwd.com"),  wwwJackwddotcom}
    };
}
