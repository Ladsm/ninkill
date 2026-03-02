#include <util/obfstr.hpp>
#include <vfs/vfs.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <util/text/longtexts.h>
std::unique_ptr<VNode> root;
VNode* cwd;
std::string cwdPath() {
	VNode* t = cwd;
	std::string p;
	while (t && t->parent) {
		p = "/" + t->name + p;
		t = t->parent;
	}
	return p.empty() ? "/" : p;
}
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
using CmdFunc = std::function<int(const std::vector<std::string>&)>;
void mkuserfiles(VNode* dir) {
	auto downloads = mkdirNode(dir, H("downloads"));
	auto documents = mkdirNode(dir, H("documents"));
	auto desktop = mkdirNode(dir, H("desktop"));
	auto audio = mkdirNode(dir, H("audio"));
	auto videos = mkdirNode(dir, H("videos"));
	auto images = mkdirNode(dir, H("images"));
}
std::string readme = 
R"(
Nuebine Incorporated Network Operating System
---------------------------------------------
Licence:
All Rights Reserved
Copyright (c) 1998 Nuebine Incorporated Network
THE CONTENTS OF THIS PROJECT ARE PROPRIETARY AND CONFIDENTIAL.
UNAUTHORIZED COPYING, TRANSFERRING OR REPRODUCTION OF THE CONTENTS OF THIS PROJECT, VIA ANY MEDIUM IS STRICTLY PROHIBITED.
The receipt or possession of the source code and/or any parts thereof does not convey or imply any right to use them
for any purpose other than the purpose for which they were provided to you.
The software is provided "AS IS", without warranty of any kind, express or implied, including but not limited to
the warranties of merchantability, fitness for a particular purpose and non infringement.
In no event shall the authors or copyright holders be liable for any claim, damages or other liability,
whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software
or the use or other dealings in the software.
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the software.

1. basic commands
-----------------
help: prints help screen or command info, usage: help <command name>
cd : change directory, usage: cd <directory name>
ls & dir : list directory, usage: ls
pwd : print working directory, usage: pwd
mkdir : make new directory, usage: mkdir <directory name>
touch : make new file, usage: touch <file name>
cat : print file contents, usage: cat <file name>
rm : remove file, usage: rm <filename> (to remove directory use: rm -r <directory name>)
clear & cls: clears screen, usage: clear
lsfs : lists filesystems, usage: lsfs
mkfs : make filesystem at device, usage: mkfs.<filesystem type> <device>

2. ninkill only commands
------------------------
nin-sys : nin system utility, usage: nin-sys <nin-sys command>
nin-iexc : internet browser, usage: nin-iexc
neon : nin package manager, usage: neon <neon command>
StartAnim : plays the start animation, usage: StartAnim

3. Downloadables
----------------
Download these via the command:
neon install <package name>

vdd : virtual dynamic disk reader
vi : simple text editor
forum : nin forum software
ninfetch : nin computer analizer
)";
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
	mkfile(bin, H("neon.exc"), giberspeak());
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
	mkfile(boot, H("System.map"), H("c0100000 T _start\nc01001a0 T init_nin_kernel\nc0101fff T nin_sys_start\n"));
	mkfile(boot, H("config"), H("CONFIG_X86=y\nCONFIG_MTRR = y\nCONFIG_MODULES = y\nCONFIG_MODVERSIONS = y\nCONFIG_NFFB_FS = y\nCONFIG_TFTCFYIS_FS = y\nCONFIG_MFS_FS = y\nCONFIG_MSDOS_FS = y\n"));
	mkfile(ninbootmgr, H("ninbootmgr.cfg"), H("set default=\"0\"\nset imgdevpath=\"/dev/fd0\"\nmenuentry \'NINKILL os, linux\' --class os{\ninsmod bios\ninsmod mfs\nset root=\'hda,nindisk\'\nlinux /boot/vmlinuz\ninitrd /boot/initrd.img\n}\n"));
	mkfile(ninbootmgr, H("stage2"), gibernelf());
	mkfile(ninbootmgr, H("device.map"), gibernelf());
	//root
	mkfile(RooT, H(".history"), H("mkfs.mfs /dev/vdd\narr /dev/vdd\nifo /dev/vdd\ncd ..\ncd bin\ncat nin-iexc.exc\nnin-sys shutdown"));
	mkfile(RooT, H(".log"), H("[1998-03-24 18:22:01] device mounted\n[1998-03-24 18:22:31] commands now logged to .history\n[1998-03-24 18:24:34] rebooting\n"));
	mkfile(RooT, H(".bashrc"), H("alias ll=\'ls\'\n"));
	//etc
	auto initd = mkdirNode(etc, H("init.d"));
	auto network = mkdirNode(etc, H("network"));
	auto sysconfig = mkdirNode(etc, H("sysconfig"));
	mkfile(etc, H("hostname"), H("ninkill-live\n"));
	mkfile(etc, H("hosts"), H("127.0.0.1 localhost\n127.0.1.1 ninkill-live\n"));
	mkfile(etc, H("passwd"), H("root:x:0:0:root:/root:/bin/bash\n"));
	mkfile(etc, H("group"), H("root:x:0:\nusers:x:100:\n"));
	mkfile(etc, H("fstab"), H("/dev/fd0   /      mfs     defaults  0 0\n/dev/hda   /mnt   nffb    defaults  0 0\n"));
	mkfile(etc, H("motd"), H("Welcome to NINKILL OS\nUnauthorized access prohibited\n"));
	mkfile(etc, H("inittab"), H("id:3:initdefault:\nsi::sysinit:/etc/init.d/rcS\n"));
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
	//mnt
	mkfile(mnt, H("README.txt"), readme);
}