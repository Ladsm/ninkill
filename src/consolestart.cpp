#include <iostream>
#include <string>
#include "boot.hpp"

std::string getcommand() {
	std::string getstring = "";
	std::getline(std::cin >> std::ws, getstring);
	return getstring;
}

void listdir() {
	std::cout << "        Directory: /mnt/\n\n";
	std::cout << " Mode     LastWriteTime       Name\n";
	std::cout << " ----     -------------       ----\n";
	std::cout << "-a----  3/24/1998 6:28 PM  NINKill.forum\n";
	std::cout << "-a----  1/14/1998 3:04 AM    help.txt   \n";
}

void help() {
	std::cout << "(c)Nuebine incorperated Network\n";
	std::cout << "Thank you for using the Nuebine incorperated Network operating system.\n";
	std::cout << "We hope you enjoy your stay!\n";
	std::cout << R"(To open the operating system write : "exc-nin")" << '\n';
	std::cout << "You are right now in the live environment, you can’t do much right now exept start the forum,\nbut heres some commands you can try:";
	std::cout << "\nhelp: displays the help screen.\nexit: exits the live environment.\nls & dir: lists the directory you're in.\n";
	std::cout << "cls & clear: clears the console\ncat [filename]: reads file to you.\n";
}

int readcommand(std::string command) {
	if (command == "exc-nin") {
		return 1;
	}
	else if (command == "ls" || command == "dir") {
		listdir();
		return 0;
	}
	else if (command == "cls" || command == "clear") {
#if defined(_WIN32)
		system("cls");
#endif
#if defined(__linux__)
		system("clear");
#endif
	}
	else if (command == "help") {
		help();
		return 0;
	}
	else if (command == "exit") {
		std::exit(0);
	}
	else if (command == "") {
		return 0;
	}
	else if (command == "\r") {
		return 0;
	}
	else {
		std::cout << "\033[31m" << "'" << command << "' is not recognized as a valid command.\n" << "Please check your spelling and try again.\n" << "\033[0m";
	}
	return 0;
}

void console() {
	std::cout << "\033[?25h";
	std::cout << "Welcome to NINKILLos!\nWrite \'help\' for more info\n";
	while (true) {
		std::cout << "[root@ninkill-live]# " << std::flush;
		std::string command = getcommand();
		int z = readcommand(command);
		if (z == 1) {
			break;
		}
	}
}