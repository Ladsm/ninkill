#include <util/obfstr.hpp>
#include <net/website.hpp>
#include <util/term/getwh.hpp>
#include <vfs/vfs.hpp>
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
void w(std::string write) {
    std::cout << write << '\n';
}
void l(int num, std::string pageName) {
    std::cout << "[" << num << "] " << pageName << "\n";
}
void wwwNuebinedotcom() {
    int page = 1;
    int choice = 1;
    if (tmpDir == nullptr) {
        tmpDir = resolvePath("/tmp");
    }
    mkfile(tmpDir, H("www.neubine.com.spp"), H(
        "#include \"spp.hpp\"\n"
        "page 1 {\n"
        "\tw(\"Welcome to Nuebine Incorporated!\");\n\tw(\"Innovating the Network Since 1990\");\n\tl(2); l(3);\n}\n"
        "page 2 {\n"
        "\tw(\"About Nuebine:\");\n\tw(\"We make all things tech—software, hardware, and more...We started in 1990 in Washington, and over the years we have grown larger and larger, from a two-man team to over fifty employees.\");\n"
        "\tl(1);\n}"
        "page 3 {\n"
        "\tw(\"Our projects: - NINKILL OS|nNINKILL OS is a small Linux-based operating system made for home users. Load it with a floppy drive like DOS.\");"
        "\tw(\" - NINKILL Internet Navigator|nA way to see things without needing to download them—just some temporary files, and when you finish using the content, the files get deleted.|n\");\n"
        "\tw(\"It uses a website maker named spp(Script++), it uses c++ to display text or get input.\");\n\tl(1);\n}"
        ));
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
            std::cout << H("It uses a website maker named spp(Script++), it uses c++ to display text or get input.\n");
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
void wwwNuebinedotcomFeedback() {
    int page = 1;
    int choice = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            std::cout << H("Feedback page:\n");
            std::cout << H("[1] Send Feedback\n");
            std::cout << H("[2] Back\n");
            std::cin >> choice;
            if (choice == 1) {
                page = 2;
            }
            if (choice == 2) {
                wwwNuebinedotcom();
                return;
            }
            else {
                std::cout << H("Not an option\n");
            }
            break;
        case 2:
            std::string feedback;
            std::getline(std::cin >> std::ws, feedback);
            page = 1;
            break;
        }
    }
}
// -Hoien Shaun Dow
void wwwNuebinedotcomLie() {
    int page = 1;
    int choice = 1;
    if (tmpDir == nullptr) {
        tmpDir = resolvePath("/tmp");
    }
    mkfile(tmpDir, H("www.neubine.com.|lie.spp"), H(
        "//bullshit, this man worked so litle here.\n"
        "//only four months, all he did was moderation on the forum and left on time.\n"
        "//he hated it, corprate were all ways talking about ways to get rid of him.\n"
        "//HoienShaunDow@www.HoienDow.net\n" // todo continue here
        "#include \"spp.hpp\"\n"
        "page 1 {\n"
        "w(\"Jack is no longer with us.|nWe found jack yesterday, in his cubicle, passed out.|nWe rushed him to the hospital, but he didn't make it.|nWe contacted his family and told them the news|nWe hope you take this well.|nFrom nin:|n\");\n"
        "w(\"He was like a brother to me, even though we just meet, I felt like he was a great person\nHe was a hard worker, worked every day, worked through the night and to the other employees's heart.|nWe wish you all the best, and to jack. We miss you.\");\n"
        "}\n"
    ));
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            w("Jack is no longer with us.\nWe found jack yesterday, in his cubicle, passed out.\nWe rushed him to the hospital, but he didn't make it.\nWe contacted his family and told them the news\nWe hope you take this well.\nFrom nin:\n");
            w("He was like a brother to me, even though we just meet, I felt like he was a great person\nHe was a hard worker, worked every day, worked through the night and to the other employees's heart.\nWe wish you all the best, and to jack. We miss you.\n");
            l(1, "Exit");
            std::cin >> choice;
            if (choice == 1) {
                wwwNuebinedotcom();
                return;
            }
            else {
                std::cout << H("Not an option\n");
            }
        }
    }
}
void wwwJackwddotcom() {
    if (tmpDir == nullptr) {
        tmpDir = resolvePath("/tmp");
    }
    mkfile(tmpDir, H("www.jackwd.com.spp"), H(
        "#include \"spp.hpp\"\n"
        "page 1 {\n\tw(\"Hello, im Jack Wilder Dean. Im a software engineer based in Texes, I made this website and the internet explorer you're in.\");\n"
        "l(1); l(2);\n}"
        "// If I only added more stuff in spp. If only."
        "page 2 {\n"
        "\tw(\"My portfolio:|n - Internet Explorer|nThis is a piece of software I made that temporarily downloads files from a server, then after 10 minutes the files get wiped from your computer.|n\");\n"
        "\tw(\"To protect from ACE, it uses a proxy server. This is a diagram of how it works:|n\");\n"
        "\tw(\"I made it, yet it was stolen from me. I knew they had it for me. It was only a matter of time)\n"
        "\tw(\""
        "\t                    .-----.         .-----------.    \n"
        "\t   .----.     Fire  |  P  |         |---Server--+ - +\n"
        "\t   |$>_ | - - - - - |--R--|         `-----+-----'   |\n"
        "\t __|____|__   Wall  |  O  | - - - - - - - |         |\n"
        "\t|PC______--|        |--X--|         .-----+-----.   |\n"
        "\t`-/.::::.\\-'     +-+  Y  +-+       |--Display--|   |\n"
        "\t `--------'       | `-----' |       `-----+-----'   |\n"
        "\t      |           |         |             |         |\n"
        "\t      + - - - - - +         + - - - - - - + - - - - +\n"
        "\t\");\nw(\"Software Employment:|n1990–1997 - Jack's Software Products|n1997–now - Head Software Engineer at Nuebine Incorporated Network|n\");\n\tl(1);\n}"
        "page 3 {"
        "\tw(\"You may have come here due to a legal notice you found in Nuebine's Network Internet Navigator.\n\");"
        "\tw(\"This all started after I made Internet Explorer in 1997. It was a piece of software I liked a lot.\nBut after two months, Nuebine made a new product named \"Network Internet Navigator\". It looked the same as my software, just with some extra Nuebine stuff.\n\");\n"
        "\tw(\"I contacted them and they lied to me.They told me they started working on it in 1996 and that I was making a false claim.\n\");"
        "\tw(\"I know they lied because the proxy servers were getting requests from Nuebine.co.us.\n\");"
        "\tw(\"I filed a legal notice demanding they show me their code.At first they told me no, but then decided to let me come in.\n\");"
        "\tw(\"On that day I went into their office.After I saw my code on their computers, I told them I demanded a cut of the profit.\n\");"
        "\tw(\"And you know what ? They agreed.They told me it was fine and let me get a job. (My self - employed ass took this as fast as I could.)\n\");"
        "\tw(\"I now work as the head software engineer with them.\nMoral of the story : Don’t steal.\n\");"
        "}"
    ));
    std::cout << H("My portfolio:\n - Internet Explorer\nThis is a piece of software I made that temporarily downloads files from a server, then after 10 minutes the files get wiped from your computer.\n");
    std::cout << H("To protect from ACE, it uses a proxy server. This is a diagram of how it works:\n");
std::cout << STATIC_DEF("                    .-----.         .-----------.    ") << '\n';
    std::cout << H("   .----.     Fire  |  P  |         |---Server--+ - +") << '\n';
    std::cout << H("   |$>_ | - - - - - |--R--|         `-----+-----'   |") << '\n';
    std::cout << H(" __|____|__   Wall  |  O  | - - - - - - - |         |") << '\n';
    std::cout << H("|PC______--|        |--X--|         .-----+-----.   |") << '\n';
    std::cout << H("`-/.::::.\\-'      +-+  Y  +-+       |--Display--|   |") << '\n';
    std::cout << H(" `--------'       | `-----' |       `-----+-----'   |") << '\n';
    std::cout << H("      |           |         |             |         |") << '\n';
    std::cout << H("      + - - - - - +         + - - - - - - + - - - - +") << '\n';
    std::cout << STATIC_DEF("Software Employment:\n1990–1997 - Jack's Software Products\n1997–now - Head Software Engineer at Nuebine Incorporated Network\n");

    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            w(H("Hello, im Jack Wilder Dean. Im a software engineer based in Texes, I made this website and the internet explorer you're in."));
            l(1, "Portfolio"); l(2, "Nuebine's theft and hire"); l(3, "Exit");
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
            std::cout << H("   .----.     Fire  |  P  |         |---Server--+ - +") << '\n';
            std::cout << H("   |$>_ | - - - - - |--R--|         `-----+-----'   |") << '\n';
            std::cout << H(" __|____|__   Wall  |  O  | - - - - - - - |         |") << '\n';
            std::cout << H("|PC______--|        |--X--|         .-----+-----.   |") << '\n';
            std::cout << H("`-/.::::.\\-'      +-+  Y  +-+       |--Display--|   |") << '\n';
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
void wwwreadmedotcom() {
    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        std::cout << H("So, why did you come to this website? For what? To try to read, me?\nIs this a joke? You're just some weird nerd who explores weird sites\n");
        std::cout << H("\n\n\n\nYou're still here... Why do you keep on reading me? For some sick plesure? You should get of the computer and talk to real people once in your life\n");
        std::cout << H("\n\nFuck off\n[1] Exit");
        std::cin >> choice;
        if (choice == 1) {
            return;
        }
        else {
            std::cout << H("Not an option\n");
        }
    }
}
void wwwnuedbcous() {
    if (tmpDir == nullptr) {
        tmpDir = resolvePath("/tmp");
    }
    mkfile(tmpDir, H("www.nuedb.co.us.spp"), H(
        "#include \"spp.hpp\"\ndb(site.database.pub)"
    ));
    int choice = 1;
    int page = 1;
    while (true) {
        mkbg();
        switch (page) {
        case 1:
            l(1, "vdd");
            l(2, "forum");
            l(3, "vi");
            l(4, "ninfetch");
            l(5, "systemtillday");
            l(6, "Exit");
            std::cin >> choice;
            if (choice == 1) {
                mkfile(tmpDir, H("vdd.ifo.exc"), H(
                    "vdd. v(1.0, 1.1, 1.2). exc=y"
                ));
            }
            if (choice == 2) {
                mkfile(tmpDir, H("forum.ifo.exc"), H(
                    "forum. v(1.0). exc=y"
                ));
            }
            if (choice == 3) {
                mkfile(tmpDir, H("vi.ifo.exc"), H(
                    "vi. v(1.*). exc=y"
                ));
            }
            if (choice == 4) {
                mkfile(tmpDir, H("ninfetch.ifo.exc"), H(
                    "ninfetch. v(1.*). exc=y"
                ));
            }
            if (choice == 5) {
                mkfile(tmpDir, H("tillpass"), H(
                    "systemtilday"
                ));
            }
            if (choice == 6) {
                return;
            }
        }
    }
}
using RouteTable = std::unordered_map<std::string, std::function<void()>>;
RouteTable buildRouter() {
    return {
        {H("www.nuebine.com"), wwwNuebinedotcom},
        {H("www.Nuebine.com"), wwwNuebinedotcom},
        {H("Nuebine.co.us"), wwwNuebinedotcom},
        {H("nuebine.co.us"), wwwNuebinedotcom},
        {H("www.jackwd.com"),  wwwJackwddotcom},
        {H("www.readme.com"), wwwreadmedotcom},
        {H("www.nuebine.com/feedback"), wwwNuebinedotcomFeedback},
        {H("www.nuebine.com/lie"), wwwNuebinedotcomLie},
        {H("www.nuedb.co.us"), wwwnuedbcous},
    };
}
