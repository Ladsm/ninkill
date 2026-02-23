#include <iostream>
#if defined(_WIN32)
#include <conio.h>
#endif
#if defined(__linux__)
#include <unistd.h>
#include <termios.h>
int getchThred() {
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
/*
+-------+   0   1   2   3   4   5   6   7   8   9
|   2   |  10  11  12  13  14  15  16  17  18  19
|-1   -2|
|   1   | Diagram of GetPlayerInput() for future me
+-------+
*/

int GetPlayerInput() {
    enum {
        down = 1,
        up = 2,
        left = -1,
        right = -2
    };
    int ch =
#ifdef _WIN32
        _getch();
#else
        getchThred();
#endif
    int returner = 0;
#ifdef _WIN32
    if (ch == 0 || ch == 0xE0) {
        switch (_getch()) {
        case 72: returner = up;    break;
        case 80: returner = down;  break;
        case 75: returner = left;  break;
        case 77: returner = right; break;
        case 48: returner = 10;    break;
        case 49: returner = 11;    break;
        case 50: returner = 12;    break;
        case 51: returner = 13;    break;
        case 52: returner = 14;    break;
        case 53: returner = 15;    break;
        case 54: returner = 16;    break;
        case 55: returner = 17;    break;
        case 56: returner = 18;    break;
        case 57: returner = 19;    break;
        }
    }
    else {
        switch (ch) {
        case 'w': case 'W': returner = up;    break;
        case 's': case 'S': returner = down;  break;
        case 'a': case 'A': returner = left;  break;
        case 'd': case 'D': returner = right; break;
        default: break;
        }
    }
#else
    if (ch == 27) {
        if (getchThred() == 91) {
            switch (getchThred()) {
            case 'A': returner = up;    break;
            case 'B': returner = down;  break;
            case 'C': returner = right; break;
            case 'D': returner = left;  break;
            }
        }
    }
    else {
        switch (ch) {
        case 'w': case 'W': returner = up;    break;
        case 's': case 'S': returner = down;  break;
        case 'a': case 'A': returner = left;  break;
        case 'd': case 'D': returner = right; break;
        case 48: returner = 10;    break;
        case 49: returner = 11;    break;
        case 50: returner = 12;    break;
        case 51: returner = 13;    break;
        case 52: returner = 14;    break;
        case 53: returner = 15;    break;
        case 54: returner = 16;    break;
        case 55: returner = 17;    break;
        case 56: returner = 18;    break;
        case 57: returner = 19;    break;
        default: break;
        }
    }
#endif
    return returner;
}