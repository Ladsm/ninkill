#include <util/obfstr.hpp>
#include <net/ninkill.hpp>
#include <boot/boot.hpp>
#include <system/core/console.hpp>
#include <system/storage/savefile.hpp>
#include <system/core/ninsys.hpp>
#include <system/storage/pkg.hpp>
#include <vfs/vfs.hpp>
#include <ui/menu.hpp>
#include <fstream>
#include <filesystem>
#include <thread>
#ifdef _WIN32
#include <windows.h>
void enableANSI() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}
#endif

void clear() {
	std::cout << H("\033[2J\033[H");
}
std::vector<Page> FoRuM;
std::vector<user> list;
std::string passwordNINIMADEthisLongSOICanOfUscaTeThisLikeHowLingdoyouthinkIcanMakeThisPleaseUnderstanmdImjustsomeOkaythatsit = H("NINEXC.exc_pkgNeon/ltxc|iexc");
void init() {
	user nin = user(H("nin"), H("NINEXC.exc_pkgNeon/ltxc|iexc"), 4);
	user john = user(H("john"), H("12345678910mod12345123451234512345qweasd123"), 3);
	user Jack = user(H("Jack Wilder Dean"), H("no...youarenotgetingmypassword"), 3);
	user hoikgrew = user(H("hoikgrew"), H("HoknGrew"), 3);
	user testmem = user(H("TEST"), H("TESTSTART"), 1);
	user jorin = user(H("jorin"), H("dfsjhjiof"), -1);
	user till = user(H("till"), H("systemtillday"), 2);
	user tomm = user(H("tomm4566"), H("4566"), 1);
	reply Gone1 = reply(H("After two years of work, fun, and more, the Ninkill forums are shutting down."), nin);
	reply Gone2 = reply(H("What? Why? This is dumb. Don’t let the words of shitty people stop your fun."), Jack);
	reply Gone3 = reply(H("Because I can’t take this shit anymore. I'm done working with dumbasses that want more and more—and for what? To get more people to hurt me?"), nin);
	reply Gtwo1 = reply(H("Do you know whats going on in the forum??? I see the pined post but dont under stand, all the posts I made are gone now?!"), tomm);
	reply Gtwo2 = reply(H("I deleted most posts if they had any small infringment of the rules, corprate am I right?"), nin);
	reply None1 = reply(H("Nuebine Incorporated Network is releasing a new version of NINKILL!!! What do you want us to add? Because I may add it >:)."), Jack);
	std::vector<reply> Whysoemptyarr = { Gtwo1, Gtwo2 };
	Post Whysoempty = Post(H("Why is the forum so empty??"), tomm, Whysoemptyarr);
	std::vector<reply> NINKILLOSNEWarr = { None1 };
	Post NINKILLOSNEW = Post(H("NINKILL v1.3 releaseing!"), Jack, NINKILLOSNEWarr);
	std::vector<reply> NINKILLPinnedarr = { Gone1, Gone2, Gone3 };
	Post NINKILLPinned = Post(H("PINNED Ninkill is takeing a break"), nin, NINKILLPinnedarr, true);
	std::vector<Post> indexarr = { NINKILLPinned, Whysoempty };
	std::vector<Post> Newsarr = { NINKILLOSNEW };
	Page News = Page{ H("News"), Newsarr };
	Page Index = Page{ H("Index"), indexarr };
	FoRuM = { Index, News };
	list = { nin ,john, Jack ,hoikgrew ,testmem ,jorin, till, tomm };
	initSysCommands();
	initFS();
	initNeon();
}
bool debug = false;
bool innin = false;
int main(int argc, char* argv[]) {
	if (checkfile() == true) {
		std::cout << "No bootable device found";
		return 0;
	}
	std::string lockPath = getAppDataPath() + H("/ninkill_sys_lock.bin");
	std::ifstream lockCheck(lockPath);
	if (lockCheck.good()) {
		std::cout << H("\033[31m");
		std::cout << H("NUEBINE INCORPORATED: ACCESS PERMANENTLY REVOKED.\n");
		std::cout << H("TERMINAL GUID: ") << H("0x80041001-FATAL\n");
		std::cout << H("Wipe detected. Further attempts logged.\n");
		std::cout << H("\033[0m");
		return 0;
	}
	lockCheck.close();
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "iopgjdiogjiogjidfogjiopgjdfiopg4789503274850934uojklsdjfklsdjfmk") == 0) {
			debug = true;
		}
	}
	std::cout << "/*do we still need this? -Hoien Shaun Dow\nprojecting much? -Jack.W Dean\nno, will we keep it? Yes. -nin\nNUEBINE WILL NEVER LET PEOPLE DATA MINE, IF YOU DO YOU ARE BRAKEING THE NIN LICENSE AND IF YOU ARE FOUND OUT TO BE USING A CRACKED VERSION OR DATAMINE OUR PRODUCTS YOU WILL BE SENT A HEFTY FINE OR THE LAW WILL CATCH UP TO YOU\n";
	clear();
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	enableANSI();
#endif
	std::string FKDEF = "ENCRT(\"OS log...\")";
	init();
reboot:
	if (!debug) {
		std::cout << SAFESTR("\033[32m");
		showBootMenu();
		std::cout << H("\ninitramfs"); threedot();
		clear();
		bootanim();
		clear();
	}
	std::cout << SAFESTR("\033[32m");
	bool usr = false;
	std::string password;
	std::cout << H("Welcome to NINKILLos!\nWrite \'help\' for more info\n");
	while (true) {
		int mode = console();
		switch (mode) {
		case 1:
			clear();
			while (!usr) {
				usr = whoiswantingin();
				if (!usr) {
					std::cout << H("Sorry... That name or password is incorect.\n");
				}
			}
			initforum();
			forum(FoRuM);
			clear();
			break;
		case 2:
			clear();
			internet();
			clear();
			break;
		case 3:
			std::cout << SAFESTR("Rebooting"); threedot();
			clear();
			goto reboot;
			break;
		case 5:
			std::cout << H("Password: ");
			std::getline(std::cin, password);
			if (password == passwordNINIMADEthisLongSOICanOfUscaTeThisLikeHowLingdoyouthinkIcanMakeThisPleaseUnderstanmdImjustsomeOkaythatsit) {
				wipeFS();
				continue;
			}
			else {
				std::cout << H("Wrong password, (check the spelling please).\n");
				std::cout << H("Hint: nin os name dot excecuteable underscore PacKaGe package manager name slash(linux) Long Term eXecuteable Con pipe internet explorer\n");
				innin = false;
				break;
			}
			wipeFS();
			break;
		case 6:
			clear();
			std::cout << H("\033[31m");
			std::cout << H("NUEBINE INCORPORATED: SESSION TERMINATED BY USER\n");
			std::cout << H("Wiping local traces"); threedot();
			std::string lockPath = getAppDataPath() + H("/ninkill_sys_lock.bin");
			std::ofstream lockFile(lockPath, std::ios::binary);
			if (lockFile.is_open()) {
				lockFile << H("WIPE_CONFIRMED_BY_BANDIT_") << std::time(nullptr);
				lockFile.close();
			}
			std::cout << H("\nGoodbye, Bandit.\n");
			std::this_thread::sleep_for(std::chrono::seconds(3));
			EXIT(0);
			break;
		}
	}
	saveForum(FoRuM);
}