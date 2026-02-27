#include "obfstr.hpp"
#include "boot.hpp"
#include "longtexts.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <unordered_set>
#include "consolestart.hpp"
#include "ninsys.hpp"

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
using CmdFunc = std::function<int(const std::vector<std::string>&)>;
std::unique_ptr<VNode> root;
VNode* cwd;

VNode* mkdirNode(VNode* parent, const std::string& name) {
	auto n = std::make_unique<VNode>(name, true, parent);
	auto ptr = n.get();
	parent->children[name] = std::move(n);
	return ptr;
}

VNode* mkfile(VNode* parent, const std::string& name, const std::string& txt) {
	auto n = std::make_unique<VNode>(name, false, parent);
	n->content = txt;
	auto ptr = n.get();
	parent->children[name] = std::move(n);
	return ptr;
}
VNode* resolvePath(const std::string& path) {
	if (path.empty()) return cwd;

	VNode* cur = (path[0] == '/') ? root.get() : cwd;

	std::stringstream ss(path);
	std::string part;

	while (std::getline(ss, part, '/')) {
		if (part.empty() || part == ".") continue;
		if (part == "..") {
			if (cur->parent) cur = cur->parent;
			continue;
		}
		auto it = cur->children.find(part);
		if (it == cur->children.end()) return nullptr;
		cur = it->second.get();
	}
	return cur;
}
std::string hashPass(const std::string& s) {
	std::hash<std::string> h;
	return std::to_string(h(s));
}
void lockDir(VNode* dir, const std::string& pass) {
	dir->locked = true;
	dir->passwordHash = hashPass(pass);
}
bool unlockDir(VNode* dir, const std::string& attempt) {
	if (!dir->locked)
		return true;
	return hashPass(attempt) == dir->passwordHash;
}
std::string cwdPath() {
	VNode* t = cwd;
	std::string p;
	while (t && t->parent) {
		p = "/" + t->name + p;
		t = t->parent;
	}
	return p.empty() ? "/" : p;
}
auto makePrompt = [] {
	VNode* t = cwd;
	std::string path;
	while (t && t->parent) { path = H("/") + t->name + path; t = t->parent; }
	if (path.empty()) path = H("/");
	return H("[root@ninkill-live ") + path + H("]# ");
	};
void mkuserfiles(VNode* dir) {
	auto downloads = mkdirNode(dir, H("downloads"));
	auto documents = mkdirNode(dir, H("documents"));
	auto desktop = mkdirNode(dir, H("desktop"));
	auto audio = mkdirNode(dir, H("audio"));
	auto videos = mkdirNode(dir, H("videos"));
	auto images = mkdirNode(dir, H("images"));
}
void initFS() {
	root = std::make_unique<VNode>("/", true, nullptr);
	cwd = root.get();
	auto bin = mkdirNode(root.get(), H("bin"));
	auto dev = mkdirNode(root.get(), H("dev"));
	auto boot = mkdirNode(root.get(), H("boot"));
	auto RooT = mkdirNode(root.get(), H("root"));
	auto mnt = mkdirNode(root.get(), H("mnt"));
	auto etc = mkdirNode(root.get(), H("etc"));
	auto proc = mkdirNode(root.get(), H("proc"));
	auto home = mkdirNode(root.get(), H("home"));
	//user folders
	auto till = mkdirNode(home, H("till"));
	lockDir(till, H("systemtilday"));
	mkuserfiles(till);
	auto tomm = mkdirNode(home, H("tomm"));
	lockDir(tomm, H("4566"));
	mkuserfiles(tomm);
	//excs
	mkfile(bin, H("nin-iexc.exc"), NINEX_EXC_TEXT);
	mkfile(bin, H("nin-fexc.exc"), NINKILL_EXC_TEXT);
	mkfile(bin, H("help.exc"), giberspeak());
	mkfile(bin, H("mkfs.exc"), giberspeak());
	mkfile(bin, H("mkfs.mfs.exc"), giberspeak());
	mkfile(bin, H("mkfs.nffb.exc"), giberspeak());
	mkfile(bin, H("mkfs.tftcfyis.exc"), giberspeak());
	mkfile(bin, H("cat.exc"), giberspeak());
	mkfile(bin, H("mkdir.exc"), giberspeak());
	mkfile(bin, H("cd.exc"), giberspeak());
	mkfile(bin, H("pwd.exc"), giberspeak());
	mkfile(bin, H("ls.exc"), giberspeak());
	mkfile(bin, H("lsfs.exc"), giberspeak());
	mkfile(bin, H("clear.exc"), giberspeak());
	mkfile(bin, H("arr.exc"), giberspeak());
	mkfile(bin, H("ifo.exc"), giberspeak());
	mkfile(bin, H("lsblk.exc"), giberspeak());
	mkfile(bin, H("reboot.exc"), giberspeak());
	mkfile(bin, H("bash.exc"), giberspeak());
	mkfile(bin, H("nin-sys.exc"), giberspeak());
	mkfile(bin, H("StartAnim.exc"), giberspeak());
	//dev
	mkfile(dev, H("loop0"), H(""));
	mkfile(dev, H("hda"), H("RAW BLOCK DEVICE\nREAD VIA DRIVER ONLY\nTRY USING ifo\n"));
	mkfile(dev, H("fd0"), H("RAW BLOCK DEVICE\nREAD VIA DRIVER ONLY\nTRY USING ifo\n"));
	mkfile(dev, H("vdd"), H("RAW BLOCK DEVICE\nREAD VIA DRIVER ONLY\nTRY USING ifo\n"));
	mkfile(dev, H("tty0"), H(""));
	mkfile(dev, H("loop0"), H(""));
	mkfile(dev, H("loop1"), H(""));
	mkfile(dev, H("loop2"), H(""));
	mkfile(dev, H("loop3"), H(""));
	mkfile(dev, "null", "");
	mkfile(dev, "zero", "");
	mkfile(dev, "random", "");
	//boot
	auto ninbootmgr = mkdirNode(boot, H("NINBOOTMGR"));
	mkfile(boot, H("vmlinuz"), gibernelf());
	mkfile(boot, H("initrd.img"), gibernelf());
	mkfile(boot, H("System.map"), H("c0100000 T _start\nc01001a0 T init_nin_kernel\nc0101fff T nin_lies\n"));
	mkfile(boot, H("config"), H("CONFIG_X86=y\nCONFIG_MTRR = y\nCONFIG_MODULES = y\nCONFIG_MODVERSIONS = y\nCONFIG_NFFB_FS = y\nCONFIG_TFTCFYIS_FS = y\nCONFIG_MFS_FS = y\nCONFIG_MSDOS_FS = y\n"));
	mkfile(ninbootmgr, H("ninbootmgr.cfg"), H("set default=\"0\"\nset imgdevpath=\"/dev/fd0\"\nmenuentry \'NINKILL os, linux\' --class os{\ninsmod bios\ninsmod mfs\nset root=\'hda,nindisk\'\nlinux /boot/vmlinuz\ninitrd /boot/initrd.img\n}\n"));
	mkfile(ninbootmgr, H("stage2"), gibernelf());
	mkfile(ninbootmgr, H("device.map"), gibernelf());
	//root
	mkfile(RooT, H(".history"), H("mkfs.mfs /dev/vdd\narr /dev/vdd\nifo /dev/vdd\ncd ..\ncd bin\ncat nin-iexc.exc\nnin-sys shutdown"));
	mkfile(RooT, H(".log"), H("[1998-03-24 18:22:01] device mounted\n[1998-03-24 18:22:31] commands now logged to .history\n[1998-03-24 18:24:34] rebooting\n"));
	mkfile(RooT, H(".bashrc"),H("alias ll=\'ls\'\n"));
	//etc
	auto initd = mkdirNode(etc, H("init.d"));
	auto network = mkdirNode(etc, H("network"));
	auto sysconfig = mkdirNode(etc, H("sysconfig"));
	mkfile(etc, H("hostname"), H("ninkill-live\n"));
	mkfile(etc, H("hosts"),H("127.0.0.1 localhost\n127.0.1.1 ninkill-live\n"));
	mkfile(etc, H("passwd"),H("root:x:0:0:root:/root:/bin/bash\n"));
	mkfile(etc, H("group"),H("root:x:0:\nusers:x:100:\n"));
	mkfile(etc, H("fstab"),H("/dev/fd0   /      mfs     defaults  0 0\n/dev/hda   /mnt   nffb    defaults  0 0\n"));
	mkfile(etc, H("motd"),H("Welcome to NINKILL OS\nUnauthorized access prohibited\n"));
	mkfile(etc, H("inittab"),H("id:3:initdefault:\nsi::sysinit:/etc/init.d/rcS\n"));
	mkfile(initd, H("rcS"), H(
		"#!/bin/sh\n"
		"# NINKILL boot script\n"
		"\n"
		"echo \"Booting NINKILL OS 1.3\"\n"
		"echo \".\"\n"
		"\n"
		"mount -t proc proc /proc\n"
		"mount -t sysfs sysfs /sys\n"
		"\n"
		"hostname --file /etc/hostname\n"
		"\n"
		"hwclock --hctosys\n"
		"echo \".\"\n"
		"\n"
		"modprobe loop\n"
		"modprobe nffb\n"
		"modprobe mfs\n"
		"echo \"initramfs\"\n"
		"echo \".\"\n"
		"\n"
		"fsck -A\n"
		"\n"
		"mount -a\n"
		"\n"
		"#Dont know why, but forum info and logs are spilling into the virtual dynamic disk.\n"
		"#I think it maybe something with the image building system we have being conected to the forum servers\n"
		"umount /mnt/vdd\n"
		"\n"
		"/bin/nin-sys start rngd\n"
		"dmesg -n 4\n"
		"/bin/nin-sys start logger\n"
		"echo \".\"\n"
		"\n"
		"/bin/nin-sys start net\n"
		"/bin/nin-sys start forums\n"
		"\n"
		"clear\n"
		"StartAnim\n"
		"clear\n"
		"\n"
		"echo \"Welcome to NINKILL OS!\"\n"
		"echo \"Type 'help' for assistance\"\n"
	));
	mkfile(network, H("interfaces"), H("auto lo\niface lo inet loopback\n"));
	mkfile(sysconfig, H("clock"), H("UTC=true\n"));
	//proc
	mkfile(proc, H("version"), H("NINKILL kernel 1.3"));
	mkfile(proc, H("filesystems"), H("nodev\tproc\nnodev\ttmpfs\n"));
	mkfile(proc, H("cmdline"), H("root=/bin/bash rw"));
}
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
	std::cout << "Directory: " << cwdPath() << "\n\n";
	for (auto& [n, node] : cwd->children)
		std::cout << (node->isDir ? "/ " : "  ") << n << "\n";
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
	{H("nin-fexc"),H("Runs forum executable")},
	{H("nin-iexc"),H("Runs internet executable")},
	{H("nin-sys"), H("System utility for power users")},
	{H("mkfs"),H("Formats a device: mkfs.<type> /dev/device")},
	{H("lsfs"),H("Lists all filesystems")},
	{H("arr"),H("Aranges filesystem for use")},
	{H("ifo"),H("Displays information about device")},
	{H("StartAnim"), H("Displays the start animation")},
	{H("lsblk"),H("Shows block devices")}
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
		if (args.size() == 1)
		{
			std::cout << H("Thank you for using NINKILL os!\nWe hoppe you enjoy your use of NINKILL os and send feedback to www.nuebine.com/feedback :)\n");
			for (const auto& [name, desc] : helpDB)
				std::cout << H("  ") << name << H("\n");
			std::cout << H("\nType help <command> for details\n");
			return 0;
		}
		std::string target = args[1];
		auto it = helpDB.find(target);
		if (it == helpDB.end())
		{
			std::cout << H("No help entry for '") << target << H("'\n");
			return 0;
		}
		std::cout << target << H(" — ") << it->second << H("\n");
		return 0;
	}
	if (cmd.rfind(H("mkfs."), 0) == 0) {
		if (args.size() < 2) {
			std::cout << STATIC_DEF("Usage: mkfs.<type> /dev/device\n");
			return 0;
		}
		std::string type = cmd.substr(5);
		std::string dev = args[1];
		if (!validFS.count(type)) {
			std::cout << H("Unknown filesystem type\n");
			std::cout << H("Supported types: nffb, mfs, tftcfyis\n");
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
	if (cmds.empty()) {
		cmds["bash"] = [](auto& a) { return 0; };
		cmds["cat"] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: cat <file>\n"; return 0; }
			VNode* f = resolvePath(a[1]);
			if (!f || f->isDir) { std::cout << "File not found\n"; return 0; }
			std::cout << f->content << "\n";
			return 0;
			};
		cmds["mkdir"] = [](auto& a) {
			if (a.size() < 2) { std::cout << "Usage: mkdir <name>\n"; return 0; }
			if (cwd->children.count(a[1])) {
				std::cout << "Already exists\n";
				return 0;
			}
			mkdirNode(cwd, a[1]);
			return 0;
			};
		cmds["cd"] = [](auto& a) {
			if (a.size() < 2) { cwd = root.get(); return 0; }
			VNode* dest = resolvePath(a[1]);
			if (dest->locked) {
				std::string input;
				std::cout << H("Password: ");
				std::getline(std::cin, input);
				if (!unlockDir(dest, input)) {
					std::cout << H("Access denied\n");
					return 0;
				}
			}
			if (!dest) { std::cout << "Directory not found\n"; return 0; }
			if (!dest->isDir) { std::cout << "Not a directory\n"; return 0; }
			cwd = dest;
			return 0;
			};
		cmds["pwd"] = [](auto&) {
			std::cout << cwdPath() << "\n";
			return 0;
			};
		cmds[H("nin-sys")] = [](auto& a) { return nin_sys_cmd(a); };
		cmds[H("nin-fexc")] = [](auto&) { return 1; };
		cmds[H("nin-iexc")] = [](auto&) { return 2; };
		cmds[H("ls")] = [](auto&) { listdir(); return 0; };
		cmds[H("dir")] = cmds[H("ls")];
		cmds[H("ll")] = cmds[H("ls")]; // alias
		cmds[H("StartAnim")] = [](auto& a) { bootanim(); return 0; };
		cmds[H("lsfs")] = [](auto&) {
			std::cout << H("All filesystem types:\n");
			std::cout << H("TYPENAME       Fullname cant be used\n");
			std::cout << H("nffb           new formated filesystem blocks\n");
	  std::cout << PROTECT("mfs            my file system\n");
			std::cout << H("tftcfyis       the filesystem that cares for you in saveing\n");
			return 0;
			};
		cmds[H("mkfs")] = [](auto&) { readcommand("mkfs."); return 0; };
		cmds[H("cls")] = [](auto&) {
			std::cout << H("\033[2J\033[H");
			return 0;
			};
		cmds[H("reboot")] = [](auto&) {
			std::cout << PROTECT("\033[2J\033[H");
			return 3;
			};
		cmds[H("clear")] = cmds[PROTECT("cls")];
		cmds[H("arr")] = [](auto& a) {
			if (a.size() < 2) { std::cout << H("Usage: arr /dev/device\n"); return 0; }
			auto dev = a[1];
			if (!devices.count(dev)) {
				std::cout << H("Unknown device\n");
				return 0;
			}
			if (devices[dev] == 1) {
				devices[dev] = 2;
				std::cout << H("Filesystem arranged\n");
			}
			else
				std::cout << H("Device not formatted\n");
			return 0;
			};
		cmds[H("ifo")] = [](auto& a) {
			if (a.size() < 2) { std::cout << H("Usage: ifo /dev/device\n"); return 0; }
			auto dev = a[1];
			if (!devices.count(dev)) {
				std::cout << H("Unknown device\n");
				return 0;
			}
			if (dev == H("/dev/hda") && devices[dev] == 2)
				std::cout << H("5 Gigabite Hard disk\n");
			if (dev == H("/dev/fd0") && devices[dev] == 2)
				std::cout << H("10 Megabite flopy\n");
			else if (dev == H("/dev/vdd") && devices[dev] == 2)
				std::cout << H("To: nin\nThe forums are becomeing unstable, we dont have moderators for this and I dont want to mod the forums on work.\nPlease talk to the higher-ups about this\n - Jack.W Dean\n");
			else
				std::cout << H("No readable info\n");
			return 0;
			};
		cmds[PROTECT("lsblk")] = [](auto&) {
			printDevices();
			return 0;
		};
	}
	auto it = cmds.find(cmd);
	if (it != cmds.end())
		return it->second(args);
	std::cout << H("Unknown command ") << cmd << '\n';
	return -1;
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