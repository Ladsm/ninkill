#include <util/term/getwh.hpp>
#include <iostream>
#include <thread>
#include <chrono>

inline void loadingSpinnerCentered(int duration_ms = 3000, std::string nexttospin = H("Loading")) {
    const char spinner[] = { '|', '/', '-', '\\' };
    std::string LoadorConecting = nexttospin;
    size_t numFrames = sizeof(spinner) / sizeof(spinner[0]);
    int frame = 0;
    int consoleWidth = getConsoleWidth();
    size_t textsizedtwo = nexttospin.size() / 2;
    int consoleHeight = getConsoleHeight();
    int topPadding = consoleHeight / 2;
    int leftPadding = consoleWidth / 2 - textsizedtwo;
    int iterations = duration_ms / 100;
    for (int i = 0; i < iterations; i++) {
        std::cout << H("\033[H");
        for (int k = 0; k < topPadding; k++) std::cout << H("\n");
        std::cout << std::string(leftPadding, ' ')
            << LoadorConecting << spinner[frame % numFrames] << std::flush;
        frame++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << H("\033[H");
}
inline void printProgress(double percentage) {
    int val = (int)(percentage * 100);
    int barWidth = 50;
    std::cout << "\r[";
    int pos = (int)(barWidth * percentage);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << val << "% " << std::flush;
}
inline void progressbar(int speed) {
    int totalSteps = 100;
    for (int i = 0; i <= totalSteps; ++i) {
        printProgress((double)i / totalSteps);
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
    std::cout << '\n';
}