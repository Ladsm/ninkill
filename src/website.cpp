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
    int choice = 1;
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
void wwwJackwddotcom() {
    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            std::cout << "Hello, im Jack Wilder Dean. Im a software engineer based in Texes, I made this website and the internet explorer you're in.\n";
            std::cout << "[1] Portfolio\n[2] Nuebine's theft and hire\n[3] Exit\n";
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
                std::cout << "Not an option\n";
            }
            break;
        case 2:
            std::cout << "My portfolio:\n - Internet Exlorer\nThis is a piece of software I made that temperarly downloads files from a server, then after 10 minutes, the files get wiped from your computer.\n";
            std::cout << "To pretect from ACE, it uses a proxy server, this is a diagram on how it works:\n";
            std::cout << R"(                    .-----.         .-----------.     )" << '\n';
            std::cout << R"(   .----.     Fire  |  P  |         |   Server  + - + )" << '\n';
            std::cout << R"(   |$>_ | - - - - - |  R  |         `-----+-----'   | )" << '\n';
            std::cout << R"( __|____|__   Wall  |  O  | - - - - - - - |         | )" << '\n';
            std::cout << R"(|PC______--|        |  X  |         .-----+-----.   | )" << '\n';
            std::cout << R"(`-/.::::.\-'      +-+  Y  +-+       |  Display  |   | )" << '\n';
            std::cout << R"( `--------'       | `-----' |       `-----+-----'   | )" << '\n';
            std::cout << R"(      |           |         |             |         | )" << '\n';
            std::cout << R"(      + - - - - - +         + - - - - - - + - - - - + )" << '\n';
            std::cout << R"(                                                      )" << '\n';
            std::cout << "Software Employment:\n1990-1997 - Jack's Software Products\n1997-now - head software engineering at Nuebine Incorporated Network\n";
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
            std::cout << "You may have come here due to a legle notice you may have found in Nuebine's Network Internet Navigator\n";
            std::cout << "This all started after I made Internet Exlorer in 1997, it was a piece of software I liked a lot.\nBut after two months, Nuebine made a new product named \"Network Internet Navigator\", it looked the same as my software, just with so extra Nuebine stuff.\n";
            std::cout << "I contacted them and they lied to me, told me that they started working on it in 1996 and that im makeing a false clam.\nI know that they lied due to the proxy servers getting reqests from Nuebine.co.us.\n";
            std::cout << "I filed a legle notice to them to show me there code, they at first told me no, but then disided to let me come in.\nOn that day, I went into there office, after I saw my code on there computers, I told them that I demand a cut of the profit.\nAnd you know what? They aggred, told me that its fine and let me get a job.(My selfemployed ass took this as fast as I could)\n";
            std::cout << "I now work as the head software engineering with them.\nMoral of the story: Dont steal.\n";
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
website jackwddotcom = website("www.jackwd.com", wwwJackwddotcom);