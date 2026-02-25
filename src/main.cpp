#include "obfstr.hpp"
#include "ninkill.hpp"
#include "boot.hpp"
#include "consolestart.hpp"
#include "savefile.hpp"
#include <filesystem>
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
//users
user nin = user(H("nin"), H("XxAdMiN123xX"), 4);
user john = user(H("john"), H("12345678910mod"), 3);
user Jack = user(H("Jack Wilder Dean"), H("no...youarenotgetingmypassword"), 3);
user hoikgrew = user(H("hoikgrew"), H("HoknGrew"), 3);
user testmem = user(H("TEST"), H("TESTSTART"), 1);
user jorin = user(H("jorin"), H("dfsjhjiof"), -1);
reply Gone1 = reply(H("After two years of work, fun, and more, the Ninkill forums are shutting down."), nin);
//replies
reply Gtwo1 = reply(H("I'm done with the harassment. You assholes can’t dox me and expect me to continue running this shit."), nin);
reply Nthree1 = reply(H("Nuebine Incorporated Network is releasing a new version of NINKILL!!! What do you want us to add? Because I may add it >:)."), Jack);
reply Gone2 = reply(H("What? Why? This is dumb. Don’t let the words of shitty people stop your fun."), Jack);
reply Gone3 = reply(H("Because I can’t take this shit anymore. I'm done working with dumbasses that want more and more—and for what? To get more people to hurt me?"), nin);
//posts
std::vector<reply> NINKILLOSNEWarr = { Nthree1 };
Post NINKILLOSNEW = Post(H("NINKILL v1.3 releaseing!"), Jack, NINKILLOSNEWarr);
std::vector<reply> NINKILLPinnedarr = { Gone1, Gone2, Gone3 };
Post NINKILLPinned = Post(H("PINNED Ninkill is takeing a break"), nin, NINKILLPinnedarr, true);
std::vector<reply> Imsickarr = { Gtwo1 };
Post Imsick = Post(H("Im sick of this"), nin, Imsickarr, true);
//pages
std::vector<Post> indexarr = { NINKILLPinned, Imsick };
std::vector<Post> Newsarr = { NINKILLOSNEW };
Page News = Page{ H("News"), Newsarr };
Page Index = Page{ H("Index"), indexarr };
std::vector<Page> FoRuM = { Index, News };
std::vector<user> list = { nin ,john, Jack ,hoikgrew ,testmem ,jorin };
void init() {
	nin = user(H("nin"), H("XxAdMiN123xX"), 4);
	john = user(H("john"), H("12345678910mod"), 3);
	Jack = user(H("Jack Wilder Dean"), H("no...youarenotgetingmypassword"), 3);
	hoikgrew = user(H("hoikgrew"), H("HoknGrew"), 3);
	testmem = user(H("TEST"), H("TESTSTART"), 1);
	jorin = user(H("jorin"), H("dfsjhjiof"), -1);
	list = { nin ,john, Jack ,hoikgrew ,testmem ,jorin };
}
void initForumData(const std::vector<user>& users, const std::vector<Page>& pages) {
	list = users;
	FoRuM = pages;
}
int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	enableANSI();
#endif
	if (!loadForumIfExists(list, FoRuM)) {
		initForumData(list, FoRuM);
		saveForum(FoRuM);
	}
	FoRuM = loadForum(list);
	init();
	reboot:
	showBootMenu();
	std::cout << H("booting"); threedot();
	std::cout << H("\ninitramfs"); threedot();
	clear();
	std::cout << H("\033[32m");
	bootanim();
	clear();
	bool usr = false;
	std::cout << H("Welcome to NINKILLos!\nWrite \'help\' for more info\n");
	while (true) {
		int mode = console();
		switch (mode) {
		case 1:
			clear();
		login:
			usr = whoiswantingin();
			if (usr == false) {
				std::cout << H("Sorry... That name or password is incorect.\n");
				goto login;
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
			std::cout << H("Rebooting"); threedot();
			clear();
			goto reboot;
			break;
		}
	}
	saveForum(FoRuM);
}