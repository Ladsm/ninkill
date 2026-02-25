#include "boot.hpp"
#include "longtexts.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <unordered_set>

#if defined(_WIN32)
#include <conio.h>
int readKey() {
	int ch = _getch();
	if (ch == 0 || ch == 224) {
		int ch2 = _getch();
		return 1000 + ch2;
	}
	return ch;
}
#else
#include <unistd.h>
#include <termios.h>
int readKey() {
	termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	int ch = getchar();
	if (ch == 27) {
		if (getchar() == '[') {
			ch = 1000 + getchar();
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

std::string getcommand()
{
	static std::vector<std::string> history;
	int historyIndex = history.size();

	std::string buf;
	size_t cursor = 0;
	const std::string prompt = "[root@ninkill-live]# ";
	auto redraw = [&]() {
		std::cout << "\33[2K\r" << prompt << buf;
		std::cout << "\r\33[" << (cursor + prompt.size()) << "C" << std::flush;
		};
	while (true) {
		int key = readKey();
		if (key == '\n' || key == '\r') {
			std::cout << "\n";
			if (!buf.empty())
				history.push_back(buf);
			return buf;
		}
		else if (key == 8 || key == 127) {
			if (cursor > 0) {
				buf.erase(cursor - 1, 1);
				cursor--;
				redraw();
			}
		}
		else if (key == 1000 + 83 || key == 1000 + '3') {
			if (cursor < buf.size()) {
				buf.erase(cursor, 1);
				redraw();
			}
		}
		else if (key == 1000 + 75 || key == 1000 + 'D') {
			if (cursor > 0) {
				cursor--;
				redraw();
			}
		}
		else if (key == 1000 + 77 || key == 1000 + 'C') {
			if (cursor < buf.size()) {
				cursor++;
				redraw();
			}
		}
		else if (key == 1000 + 72 || key == 1000 + 'A') {
			if (historyIndex > 0) {
				historyIndex--;
				buf = history[historyIndex];
				cursor = buf.size();
				redraw();
			}
		}
		else if (key == 1000 + 80 || key == 1000 + 'B') {
			if (historyIndex < (int)history.size() - 1) {
				historyIndex++;
				buf = history[historyIndex];
			}
			else {
				historyIndex = history.size();
				buf.clear();
			}
			cursor = buf.size();
			redraw();
		}
		else if (key >= 32 && key <= 126) {
			buf.insert(cursor, 1, (char)key);
			cursor++;
			redraw();
		}
	}
}
std::unordered_map<std::string, int> devices = {
	{"/dev/hda",2},
	{"/dev/fd0",2},
	{"/dev/vdc",0}
};
std::vector<std::string> tokenize(const std::string& line)
{
	std::istringstream iss(line);
	std::vector<std::string> out;
	std::string s;
	while (iss >> s)
		out.push_back(s);
	return out;
} using CmdFunc = std::function<int(const std::vector<std::string>&)>;
void listdir() {
	std::cout << "                 Directory: /mnt/\n\n";
	std::cout << " Mode     LastWriteTime       Name         Size   \n";
	std::cout << " ----     -------------       ----         ----   \n";
	std::cout << "-a----  3/24/1998 6:28 PM  NINKill.exc   2,865kb  \n";
	std::cout << "-a----  4/26/1997 8:02 PM   NINEX.exc    6,462kb  \n";
}
void printDevices() {
	std::cout << "NAME  SIZE   TYPE   MOUNTPOINTS\n";
	for (const auto& [name, state] : devices){
		std::string shortName = name.substr(5);
		std::string size;
		std::string type;
		std::string mount;
		if (name == "/dev/hda") {
			size = "5.05GB";
			type = " disk";
			mount = " /mnt";
		}
		else if (name == "/dev/fd0") {
			size = "10.3MB";
			type = " flopy";
			mount = "/";
		}
		else if (name == "/dev/vdc") {
			size = " 5MB";
			type = "   loop";
			mount = " /dev";
		}
		std::cout
			<< shortName << "  "
			<< size << " "
			<< type << "      "
			<< mount << "\n";
	}
}
const std::unordered_set<std::string> validFS = {
	"nffb",
	"mfs",
	"tftcfyis"
};
const std::unordered_map<std::string, std::string> helpDB = {
	{"help","Shows help information"},
	{"ls", "Lists the directory you're in"},
	{"dir","Alias for ls"},
	{"cls","Clears the screen"},
	{"clear","Alias for cls"},
	{"nin-fexc","Runs forum executable"},
	{"nin-iexc","Runs internet executable"},
	{"mkfs","Formats a device: mkfs.<type> /dev/device"},
	{"lsfs","Lists all filesystems"},
	{"arr","Aranges filesystem for use"},
	{"ifo","Displays information about device"},
	{"lsblk","Shows block devices"}
};
int readcommand(const std::string& line)
{
	auto args = tokenize(line);
	if (args.empty()) return 0;
	const std::string& cmd = args[0];
	if (cmd == "help")
	{
		if (args.size() == 1)
		{
			std::cout << "Available commands:\n";
			for (const auto& [name, desc] : helpDB)
				std::cout << "  " << name << "\n";
			std::cout << "\nType help <command> for details\n";
			return 0;
		}
		std::string target = args[1];
		auto it = helpDB.find(target);
		if (it == helpDB.end())
		{
			std::cout << "No help entry for '" << target << "'\n";
			return 0;
		}
		std::cout << target << " — " << it->second << "\n";
		return 0;
	}
	if (cmd.rfind("mkfs.", 0) == 0) {
		if (args.size() < 2) {
			std::cout << "Usage: mkfs.<type> /dev/device\n";
			return 0;
		}
		std::string type = cmd.substr(5);
		std::string dev = args[1];
		if (!validFS.count(type)) {
			std::cout << "Unknown filesystem type\n";
			std::cout << "Supported types: nffb, mfs, tftcfyis\n";
			return 0;
		}
		if (!devices.count(dev)) {
			std::cout << "Device not found\n";
			return 0;
		}
		devices[dev] = 1;
		std::cout << "Formatting " << dev << " as " << type << " filesystem... Done\n";
		return 0;
	}
	static std::unordered_map<std::string, CmdFunc> cmds;

	if (cmds.empty())
	{
		cmds["nin-fexc"] = [](auto&) { return 1; };
		cmds["nin-iexc"] = [](auto&) { return 2; };
		cmds["ls"] = [](auto&) { listdir(); return 0; };
		cmds["dir"] = cmds["ls"];
		cmds["lsfs"] = [](auto&) {
			std::cout << "All filesystem types:\n";
			std::cout << "TYPENAME       Fullname cant be used\n";
			std::cout << "nffb           new formated filesystem blocks\n";
			std::cout << "mfs            my file system\n";
			std::cout << "tftcfyis       the filesystem that cares for you in saveing\n";
			return 0;
			};
		cmds["cls"] = [](auto&) {
			std::cout << "\033[2J\033[H";
			return 0;
			};
		cmds["clear"] = cmds["cls"];
		cmds["arr"] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: arr /dev/device\n"; return 0; }
			auto dev = a[1];
			if (!devices.count(dev)) {
				std::cout << "Unknown device\n";
				return 0;
			}
			if (devices[dev] == 1) {
				devices[dev] = 2;
				std::cout << "Filesystem arranged\n";
			}
			else
				std::cout << "Device not formatted\n";
			return 0;
			};
		cmds["ifo"] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: ifo /dev/device\n"; return 0; }
			auto dev = a[1];
			if (!devices.count(dev)) {
				std::cout << "Unknown device\n";
				return 0;
			}
			if (dev == "/dev/fd0" && devices[dev] == 2)
				std::cout << "10 Megabite flopy\n";
			else if (dev == "/dev/vdc" && devices[dev] == 2)
				std::cout << "To: Jack.W Dean\nThe forums are becomeing unstable, we dont have moderators for this and I dont want to mod the forums on work.\nPlease talk to the higher-ups about this\n - Jack.W Dean\n";
			else
				std::cout << "No readable info\n";
			return 0;
			};
		cmds["lsblk"] = [](auto&) {
			printDevices();
			return 0;
			};
	}
	if (line == "cat NINKill.exc") {
		std::cout << NINKILL_EXC_TEXT << "\n";
		return 0;
	}
	if (line == "cat NINEX.exc") {
		std::cout << NINEX_EXC_TEXT << "\n";
		return 0;
	}
	auto it = cmds.find(cmd);
	if (it != cmds.end())
		return it->second(args);
	std::cout << "Unknown command " << cmd << '\n';
	return -1;
}

int console() {
	std::cout << "\033[32m";
	std::cout << "\033[?25h";
	while (true) {
		std::cout << "\033[32m";
		std::cout << "\033[?25h";
		std::cout << "[root@ninkill-live]# " << std::flush;
		std::string command = getcommand();
		int z = readcommand(command);
		if (z == 1)
			return 1;
		if (z == 2)
			return 2;
		if (z == 3)
			return 3;
	}
}