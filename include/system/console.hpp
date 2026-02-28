#pragma once
#include <string>
#include <vector>
int console();
int readKey();
std::string getcommand();
std::vector<std::string> tokenize(const std::string& line);
void listdir();
void printDevices();
void EXIT(int code);
int readcommand(const std::string& line);
