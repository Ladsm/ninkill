#include <util/obfstr.hpp>
#include <boot/boot.hpp>
#include <util/term/getwh.hpp>
#include <util/term/beep.h>
#include <ui/userinput.hpp>
#include <net/page.hpp>
#include <net/website.hpp>
#include <ui/spiner.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#include <algorithm>
std::string hiddenstring() {
    if (currentuser.level <= 2) {
        return H("3-NUBINE US A HSAM LIS|TE   TI ME ");
    }
    else {
        return "";
    }
}
extern std::vector<user> list;
extern std::vector<Page> FoRuM;
std::string menuops[3] = { H("   1-Forum Index     "), H("2-News     "), hiddenstring() };
static size_t langthofopts() {
    size_t langth = 0;
    for (int i = 0; i < 3; i++) {
        langth += menuops[i].size();
    }
    return langth;
}
static void orangebk() {
    std::cout << H("\033[48;2;255;165;0m");
    std::cout << H("\033[30m");
    std::cout << H("\033[2J");
    for (int i = 0; i < 1000; i++) std::cout << H(" ");
    std::cout << H("\033[H");
}
void printBlackBar(int row) {
    int width = getConsoleWidth();
    if (width <= 0) width = 80;
    std::cout << H("\033[") << row << H(";0H");
    std::cout << H("\033[40m\033[38;2;255;165;0m");
    std::cout << std::string(width, ' ');
    std::cout << H("\033[0m");
}
void printMenuLine(int row, const std::string& leftText, const std::string& rightText, const std::string& righterText = "") {
    int width = getConsoleWidth();
    if (width <= 0) width = 80;
    std::cout << H("\033[") << row << H(";0H");
    std::cout << H("\033[40m\033[38;2;255;165;0m");
    std::string line = leftText + rightText + righterText;
    if ((int)line.length() > width) {
        line = line.substr(0, width);
    }
    std::cout << line;
    int padding = width - (int)line.length();
    if (padding > 0) {
        std::cout << std::string(padding, ' ');
    }
    std::cout << H("\033[0m");
}
void initforum() {
    std::cout << H("\033[?25l");
    ensureConsoleInitialized();
    orangebk();
    blop(1000, 500);
    loadingSpinnerCentered(3000, H("Loading"));
    blop(100, 500);
    loadingSpinnerCentered(1000, H("Conecting"));
    blop(10, 500);
    printBlackBar(2);
    printMenuLine(3, menuops[0], menuops[1], menuops[2]);
    printBlackBar(4);
}
void reDrawAll() {
    std::cout << H("\033[2J\033[H");
    orangebk();
    printBlackBar(2);
    printMenuLine(3, menuops[0], menuops[1], menuops[2]);
    printBlackBar(4);
}
void drawPage(const Page& page, int selectedPost) {
    int startRow = 6;
    std::cout << H("\033[H");
    std::cout << H("\033[1m") << page.title << H("\033[0m\n");
    for (size_t i = 0; i < page.posts.size(); i++) {
        const Post& p = page.posts[i];
        std::cout << H("\033[") << (startRow + i) << H(";5H");
        if ((int)i == selectedPost)
            std::cout << H("\033[7m");
        std::cout << p.title << H(" (by ") << p.poster.name
            << H(", ") << p.replies.size() << H(" replies)")
            << H("\033[0m");
    }
    std::cout.flush();
}
void drawPost(Post& post) {
    reDrawAll();
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    if (width <= 0) width = 80;
    printBlackBar(1);
    printMenuLine(2, H("           "), post.title);
    printMenuLine(3, H("           "), H("by: ") + post.poster.name);
    printBlackBar(4);
    int row = 5;
    for (size_t i = 0; i < post.replies.size(); i++) {
        const reply& r = post.replies[i];
        std::string prefix = std::to_string(i + 1) + H(". ");
        int maxLen = width - (int)prefix.length() - 1;
        if (maxLen <= 0) maxLen = 1;
        size_t pos = 0;
        bool firstLine = true;
        while (pos < r.paragraph.length() && row <= height) {
            std::string line = r.paragraph.substr(pos, maxLen);
            std::cout << H("\033[") << row << H(";0H") << H("\033[48;2;255;165;0m") << H("\033[30m");
            if (firstLine) {
                std::cout << prefix << line;
                firstLine = false;
            }
            else {
                std::cout << std::string(prefix.length(), ' ') << line;
            }
            int currentLineLen = (firstLine ? prefix.length() : prefix.length()) + line.length();
            int remaining = width - currentLineLen;
            if (remaining > 0)
                std::cout << std::string(remaining, ' ');

            std::cout << H("\033[0m");
            pos += maxLen;
            row++;
        }

        if (row <= height) {
            std::cout << H("\033[") << row << H(";0H") << H("\033[48;2;255;165;0m\033[30m") << H(" - ") << r.replyer.name;
            int footerPadding = width - 4 - (int)r.replyer.name.length();
            if (footerPadding > 0)
                std::cout << std::string(footerPadding, ' ');
            std::cout << H("\033[0m");
            row++;
        }
    }
    std::cout.flush();
}
void forum(std::vector<Page>& forumPages) {
    int currentPage = 0;
    int selectedPost = 0;
    bool inPostView = false;
    if (currentuser.level == 2) {
        reply Gthree = reply(H("Nuebine is lieing to to you, I know what iyu wanyt , dotnt let htem goeit to you. save yoursetlft frotm tehm, plaase listem to me. I wonr bet he last. the sydtem passewkrd itj DATAMINE***BRAKEING***NIN"), list[2]);
        std::vector<reply> SoNuebinearr = { Gthree };
        Post nubine = Post(H("NUEBINE IS A SHAM"), list[2], SoNuebinearr);
        std::vector<Post> nubinearr = { nubine };
        Page NUBINEISALIE = Page{ H("SYSTEM OVERRIDE"), nubinearr };
        forumPages.push_back(NUBINEISALIE);
    }
    else {
        menuops[2] = "";
    }
    reDrawAll();
    drawPage(forumPages[currentPage], selectedPost);
    while (true) {
        InputType input = GetPlayerInput();
        if (!inPostView) {
            switch (input) {
            case InputType::MoveUp:
                if (selectedPost > 0) selectedPost--;
                break;
            case InputType::MoveDown:
                if (selectedPost < (int)forumPages[currentPage].posts.size() - 1)
                    selectedPost++;
                break;
            case InputType::Top1: currentPage = 0; selectedPost = 0; reDrawAll(); break;
            case InputType::Top2: currentPage = 1; selectedPost = 0; reDrawAll(); break;
            case InputType::Top3:
                if (forumPages.size() > 2) {
                    currentPage = 2;
                    selectedPost = 0;
                    reDrawAll();
                }
                else {
                    blop(100, 400);
                }
                break;
            case InputType::Enter:
                if (!forumPages[currentPage].posts.empty()) {
                    inPostView = true;
                    drawPost(forumPages[currentPage].posts[selectedPost]);
                }
                break;
            case InputType::Escape:
                return;
            default: break;
            }
            if (!inPostView) {
                drawPage(forumPages[currentPage], selectedPost);
            }
        }
        else {
            if (input == InputType::Escape) {
                inPostView = false;
                reDrawAll();
                drawPage(forumPages[currentPage], selectedPost);
            }
        }
    }
}