#include <system/ninsys.hpp>
#include <boot/boot.hpp>
#include <system/console.hpp>
#include <system/pkg.hpp>
#include <util/longtexts.h>
#include <util/obfstr.hpp>
#include <vfs/vfs.hpp>
#include <ui/userinput.hpp>
#include <programs/vi.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <unordered_set>

auto makePrompt = [] {
	VNode* t = cwd;
	std::string path;
	while (t && t->parent) { path = H("/") + t->name + path; t = t->parent; }
	if (path.empty()) path = H("/");
	return H("[root@ninkill-live ") + path + H("]# ");
	};
std::string getcommand() {
	static std::vector<std::string> history;
	int historyIndex = history.size();
	std::string buf;
	size_t cursor = 0;
	const std::string prompt = makePrompt();
	auto redraw = [&]() {
		std::cout << H("\33[2K\r") << prompt << buf;
		std::cout << H("\r\33[") << (cursor + prompt.size()) << H("C") << std::flush;
		};
	while (true) {
		int key = readKey();
		if (key == '\n' || key == '\r') {
			std::cout << H("\n");
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
	{H("/dev/hda"),2},
	{H("/dev/fd0"),2},
	{H("/dev/vdd"),0}
};
std::vector<std::string> tokenize(const std::string& line) {
	std::istringstream iss(line);
	std::vector<std::string> out;
	std::string s;
	while (iss >> s)
		out.push_back(s);
	return out;
} using CmdFunc = std::function<int(const std::vector<std::string>&)>;
void listdir() {
	std::cout << "Directory: " << cwdPath() << "\n";
	for (auto& [n, node] : cwd->children)
		std::cout << (node->isDir ? "|/" : "| ") << n << "\n";
}
void printDevices() {
	std::cout << H("NAME  SIZE   TYPE             MOUNTPOINTS\n");
	for (const auto& [name, state] : devices){
		std::string shortName = name.substr(5);
		std::string size;
		std::string type;
		std::string mount;
		if (name == H("/dev/hda")) {
			size = H("5.05GB");
			type = H(" disk");
			mount = H("              /mnt");
		}
		else if (name == H("/dev/fd0")) {
			size = H("10.3MB");
			type = H(" flopy");
			mount = H("             /");
		}
		else if (name == H("/dev/vdd")) {
			size = H(" 5MB");
			type = H(" Virtual Dynamic Disk");
			mount = H("/dev");
		}
		std::cout
			<< shortName << H("  ")
			<< size << H(" ")
			<< type << H("      ")
			<< mount << H("\n");
	}
}
const std::unordered_set<std::string> validFS = {
	H("nffb"),
	H("mfs"),
	H("tftcfyis")
};
const std::unordered_map<std::string, std::string> helpDB = {
	{H("help"),H("Shows help information")},
	{H("ls"), H("Lists the directory you're in")},
	{H("dir"),H("Alias for ls")},
	{H("cd"), H("Changes directory")},
	{H("cat"), H("Displays raw text of file")},
	{H("pwd"), H("Prints working directory")},
	{H("cls"),H("Clears the screen")},
	{H("clear"),H("Alias for cls")},
	{H("neon"), H("Neon package manager")},
	{H("nin-fexc"),H("Runs forum executable")},
	{H("nin-iexc"),H("Runs internet executable")},
	{H("nin-sys"), H("System utility for power users")},
	{H("mkfs"),H("Formats a device: mkfs.<type> /dev/device")},
	{H("lsfs"),H("Lists all filesystems")},
	{H("arr"),H("Aranges filesystem for use")},
	{H("ifo"),H("Displays information about device")},
	{H("StartAnim"), H("Displays the start animation")},
	{H("lsblk"),H("Shows block devices")},
	{ H("rm"), H("Removes a file or empty directory")}
};
void EXIT(int code) {
	std::exit(code);
}
int readcommand(const std::string& line) {
	auto args = tokenize(line);
	if (args.empty()) return 0;
	const std::string& cmd = args[0];
	auto local = cwd->children.find(cmd);
	if (local != cwd->children.end() && local->second->isExec)
		return local->second->execFunc(args);
	if (cmd.find('/') != std::string::npos || cmd.rfind("./", 0) == 0) {
		VNode* node = resolvePath(cmd);
		if (node && node->isExec)
			return node->execFunc(args);
		if (node && !node->isExec) {
			std::cout << "Not executable\n";
			return 0;
		}
		std::cout << "Command not found\n";
		return 0;
	}
	if (cmd == H("help")) {
		if (args.size() == 1) {
			std::cout << H("|Thank you for using NINKILL os!\n|We hope you enjoy your use of NINKILL os and send feedback to ://www.nuebine.com :)\n|");
			std::cout << H("Use neon to use the package manager\n|Use nin-sys for system commands\n|All commands:\n");
			for (const auto& [name, desc] : helpDB) {
				std::cout << '|' << name << '\n';
			}
			std::cout << H("|Type help <command> for details\n");
			return 0;
		}
		std::string target = args[1];
		auto it = helpDB.find(target);
		if (it == helpDB.end()) {
			std::cout << H("No help entry for '") << target << H("'\n");
			return 0;
		}
		std::cout << target << H(" — ") << it->second << H("\n");
		return 0;
	}
	if (cmd.rfind(H("mkfs."), 0) == 0) {
		if (args.size() < 2) {
			std::cout << H("Usage: mkfs.<type> /dev/device\n");
			return 0;
		}
		std::string type = cmd.substr(5);
		std::string dev = args[1];
		if (!validFS.count(type)) {
			std::cout << H("Unknown filesystem type\nSupported types: nffb, mfs, tftcfyis\n");
			return 0;
		}
		if (!devices.count(dev)) {
			std::cout << H("Device not found\n");
			return 0;
		}
		devices[dev] = 1;
		std::cout << H("Formatting ") << dev << H(" as ") << type << H(" filesystem... Done\n");
		return 0;
	}
	static std::unordered_map<std::string, CmdFunc> cmds;
	if (packagesz[4].downloaded && cmds.find("nin-show") == cmds.end()) {
		cmds["nin-show"] = [](auto& a) {
			for (size_t i = 0; i < ninfetch.size(); i++) std::cout << ninfetch[i];
			return 0;
			};
	}
	if (packagesz[3].downloaded && cmds.find("vi") == cmds.end()) {
		cmds["vi"] = [](auto& a) {
			Vi(a);
			return 0;
			};
	}
	if (cmds.find(H("ls")) == cmds.end()) {
		cmds[H("bash")] = [](auto& a) { return 0; };
		cmds[H("ls")] = [](auto&) { listdir(); return 0; };
		cmds[H("dir")] = cmds[H("ls")];
		cmds[H("ll")] = cmds[H("ls")];
		cmds[H("pwd")] = [](auto&) { std::cout << cwdPath() << "\n"; return 0; };
		cmds[H("clear")] = [](auto& a) { std::cout << H("\033[2J\033[H"); return 0; };
		cmds[H("cls")] = cmds[H("clear")];
		cmds[H("cat")] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: cat <file>\n"; return 0; }
			VNode* f = resolvePath(a[1]);
			if (!f || f->isDir) { std::cout << "File not found\n"; return 0; }
			std::cout << f->content << "\n";
			return 0;
			};
		cmds[H("mkdir")] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: mkdir <name>\n"; return 0; }
			if (cwd->children.count(a[1])) { std::cout << "Already exists\n"; return 0; }
			mkdirNode(cwd, a[1]);
			return 0;
			};
		cmds[H("touch")] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: touch <name>\n"; return 0; }
			if (cwd->children.count(a[1])) { std::cout << "File Already exists\n"; return 0; }
			mkfile(cwd, a[1], "");
			return 0;
			};
		cmds[H("cd")] = [](auto& a) {
			if (a.size() < 2) { cwd = root.get(); return 0; }
			VNode* dest = resolvePath(a[1]);
			if (!dest) { std::cout << "Directory not found\n"; return 0; }
			if (!dest->isDir) { std::cout << "Not a directory\n"; return 0; }
			if (dest->locked) {
				std::string input;
				std::cout << H("Password: ");
				std::getline(std::cin, input);
				if (!unlockDir(dest, input)) { std::cout << H("Access denied\n"); return 0; }
			}
			cwd = dest;
			return 0;
			};
		cmds[H("rm")] = [](auto& a) {
			if (a.size() < 2) {
				std::cout << "Usage: rm [-r] <path>\n";
				return 0;
			}
			bool recursive = false;
			std::string path;
			if (a[1] == "-r" || a[1] == "-rf") {
				if (a.size() < 3) { std::cout << "rm: missing operand\n"; return 0; }
				recursive = true;
				path = a[2];
			}
			else {
				path = a[1];
			}
			VNode* target = resolvePath(path);
			if (!target) {
				std::cout << "rm: cannot remove '" << path << "': No such file or directory\n";
				return 0;
			}
			if (target == root.get() || target == cwd) {
				std::cout << "rm: cannot remove: Device or resource busy\n";
				return 0;
			}
			if (target->isDir && !recursive) {
				std::cout << "rm: cannot remove '" << path << "': Is a directory\n";
				return 0;
			}
			if (target->parent) {
				target->parent->children.erase(target->name);
			}
			return 0;
			};
		cmds[H("nin-sys")] = [](auto& a) { return nin_sys_cmd(a); };
		cmds[H("nin-fexc")] = [](auto&) { return 1; };
		cmds[H("nin-iexc")] = [](auto&) { return 2; };
		cmds[H("neon")] = [](auto& a) { return neon_cmd(a); };
		cmds[H("StartAnim")] = [](auto& a) { bootanim(); return 0; };
		cmds[H("lsfs")] = [](auto&) {
			std::cout << H("All filesystem types:\nTYPENAME       Fullname\n");
			std::cout << H("nffb           new formated filesystem blocks\n");
			std::cout << H("mfs            managed file system\n");
			return 0;
			};
	}
	auto it = cmds.find(cmd);
	if (it != cmds.end()) return it->second(args);
	std::cout << "Unknown command " << cmd << "\n";
	return 0;
}
int console() {
	std::cout << H("\033[32m");
	std::cout << H("\033[?25h");
	while (true) {
		std::cout << PROTECT("\033[32m");
		std::cout << H("\033[?25h");
		std::cout << makePrompt() << std::flush;
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