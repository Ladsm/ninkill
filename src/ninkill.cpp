#include "boot.hpp"
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
#include "beep.h"
#include "userinput.hpp"
#include "page.hpp"

std::string menuops[2] = {"   1-Forum Index     ", "2-News     "};
static int langthofopts() {
    size_t langth = 0;
    for (int i = 0; i < 2; i++) {
        langth += menuops[i].size();
    }
    return langth;
}

static void orangebk() {
    std::cout << "\033[48;2;255;165;0m";
    std::cout << "\033[30m";
    std::cout << "\033[2J";
    for (int i = 0; i < 1000; i++) std::cout << " ";
    std::cout << "\033[H";
}
int getConsoleWidth() {
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
int getConsoleHeight() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) return w.ws_row;
#endif
    return 25;
}

void loadingSpinnerCentered(int duration_ms = 3000, bool loadorconect = false) {
    const char spinner[] = { '|', '/', '-', '\\' };
    std::string LoadorConecting = "Loading ";
    if(loadorconect == true){ LoadorConecting = "Conecting "; }
    size_t numFrames = sizeof(spinner) / sizeof(spinner[0]);
    int frame = 0;
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int topPadding = consoleHeight / 2;
    int leftPadding = consoleWidth / 2 - 7;
    int iterations = duration_ms / 100;
    for (int i = 0; i < iterations; i++) {
        std::cout << "\033[H";
        for (int k = 0; k < topPadding; k++) std::cout << "\n";
        std::cout << std::string(leftPadding, ' ')
            << LoadorConecting << spinner[frame % numFrames] << std::flush;
        frame++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\033[H";
}
void printBlackBar(int row) {
    int width = getConsoleWidth();
    std::cout << "\033[" << row << ";0H";
    std::cout << "\033[40m\033[38;2;255;165;0m";
    std::cout << std::string(width, ' ');
    std::cout << "\033[0m";
}

void printMenuLine(int row, const std::string& leftText, const std::string& rightText) {
    int width = getConsoleWidth();
    std::cout << "\033[" << row << ";0H";
    std::cout << "\033[40m\033[38;2;255;165;0m";
    std::string line = leftText + rightText;
    if ((int)line.length() > width) {
        line = line.substr(0, width);
    }
    else {
        line += std::string(width - line.length(), ' ');
    }
    std::cout << line;
    std::cout << "\033[0m";
}

void initforum() {
    std::cout << "\033[?25l";
    ensureConsoleInitialized();
    orangebk();
    blop(1000, 500);
    loadingSpinnerCentered(3000, false);
    blop(100, 500);
    loadingSpinnerCentered(1000, true);
    blop(10, 500);
    printBlackBar(2);
    printMenuLine(3, menuops[0], menuops[1]);
    printBlackBar(4);
}
void redrawall() {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
    orangebk();
    printBlackBar(2);
    printMenuLine(3, menuops[0], menuops[1]);
    printBlackBar(4);
}
int activeTopTab = 0;
int forumSelection = 0;
int currentPage = 0;
int selectedPost = 0;
bool running = true;
void drawPage(const Page& page, int selectedPost) {
    int width = getConsoleWidth();
    int startRow = 6;
    std::cout << "\033[H";
    std::cout << "\033[1m" << page.title << "\033[0m\n";
    for (size_t i = 0; i < page.posts.size(); i++) {
        const Post& p = page.posts[i];
        std::cout << "\033[" << (startRow + i) << ";5H";
        if ((int)i == selectedPost)
            std::cout << "\033[7m";
        std::cout << p.title << " (by " << p.poster.name
            << ", " << p.replies.size() << " replies)"
            << "\033[0m";
    }
    std::cout.flush();
}
void drawPost(Post& post) {
    redrawall();
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    printBlackBar(1);
    printMenuLine(2, "           ", post.title);
    printMenuLine(3, "           ", "by: " + post.poster.name);
    printBlackBar(4);
    int row = 5;
    for (size_t i = 0; i < post.replies.size(); i++) {
        const reply& r = post.replies[i];
        std::string prefix = std::to_string(i + 1) + ". ";
        size_t maxLen = width - prefix.length() - 1;
        size_t pos = 0;
        bool firstLine = true;
        while (pos < r.paragraph.length() && row <= height) {
            std::string line = r.paragraph.substr(pos, maxLen);
            std::cout << "\033[" << row << ";0H" << "\033[48;2;255;165;0m"<< "\033[30m";

            if (firstLine) {
                std::cout << prefix << line;
                firstLine = false;
            }
            else {
                std::cout << std::string(prefix.length(), ' ') << line;
            }
            int remaining = width - ((firstLine) ? prefix.length() + line.length() : prefix.length() + line.length());
            if (remaining > 0)
                std::cout << std::string(remaining, ' ');
            std::cout << "\033[0m";
            pos += maxLen;
            row++;
        }
        if (row <= height) {
            std::cout << "\033[" << row << ";0H"
                << "\033[48;2;255;165;0m\033[30m"
                << " - " << r.replyer.name
                << std::string(width - 4 - r.replyer.name.length(), ' ')
                << "\033[0m";
            row++;
        }
    }

    std::cout.flush();
}
void forum(std::vector<Page>& forumPages) {
    int currentPage = 0;
    int selectedPost = 0;
    bool inPostView = false;
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
            case InputType::Top1:
                redrawall();
                currentPage = 0; selectedPost = 0; break;
            case InputType::Top2:
                redrawall();
                currentPage = 1; selectedPost = 0; break;
            case InputType::Enter:
                inPostView = true;
                drawPost(forumPages[currentPage].posts[selectedPost]);
                break;
            case InputType::Escape:
                return;
            default: break;
            }
            if (!inPostView)
                drawPage(forumPages[currentPage], selectedPost);
        }
        else {
            switch (input) {
            case InputType::Escape:
                redrawall();
                drawPage(forumPages[currentPage], selectedPost);
                inPostView = false;
                break;
            default: break;
            }
        }
    }
}