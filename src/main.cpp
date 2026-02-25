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
	std::cout << "\033[2J\033[H";
}
//users
user nin = user("nin", "XxAdMiN123xX", 4);
user john = user("john", "12345678910mod", 3);
user Jack = user("Jack Wilder Dean", "no...youarenotgetingmypassword", 3);
user hoikgrew = user("hoikgrew", "HoknGrew", 3);
user testmem = user("TEST", "TESTSTART", 1);
user jorin = user("jorin", "dfsjhjiof", -1);
reply Gone1 = reply("After two years of work, fun, and more, the Ninkill forums are shutting down.", nin);
//replies
reply Gtwo1 = reply("I'm done with the harassment. You assholes can’t dox me and expect me to continue running this shit.", nin);
reply Nthree1 = reply("Nuebine Incorporated Network is releasing a new version of NINKILL!!! What do you want us to add? Because I may add it >:).", Jack);
reply Gone2 = reply("What? Why? This is dumb. Don’t let the words of shitty people stop your fun.", Jack);
reply Gone3 = reply("Because I can’t take this shit anymore. I'm done working with dumbasses that want more and more—and for what? To get more people to hurt me?", nin);
//posts
std::vector<reply> NINKILLOSNEWarr = { Nthree1 };
Post NINKILLOSNEW = Post("NINKILL v1.3 releaseing!", Jack, NINKILLOSNEWarr);
std::vector<reply> NINKILLPinnedarr = { Gone1, Gone2, Gone3 };
Post NINKILLPinned = Post("PINNED Ninkill is takeing a break", nin, NINKILLPinnedarr, true);
std::vector<reply> Imsickarr = { Gtwo1 };
Post Imsick = Post("Im sick of this", nin, Imsickarr, true);
//pages
std::vector<Post> indexarr = { NINKILLPinned, Imsick };
std::vector<Post> Newsarr = { NINKILLOSNEW };
Page News = Page{ "News", Newsarr };
Page Index = Page{ "Index", indexarr };
std::vector<Page> FoRuM = { Index, News };
std::vector<user> list = { nin ,john, Jack ,hoikgrew ,testmem ,jorin };
void init() {
	nin = user("nin", "XxAdMiN123xX", 4);
	john = user("john", "12345678910mod", 3);
	Jack = user("Jack Wilder Dean", "no...youarenotgetingmypassword", 3);
	hoikgrew = user("hoikgrew", "HoknGrew", 3);
	testmem = user("TEST", "TESTSTART", 1);
	jorin = user("jorin", "dfsjhjiof", -1);
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
	//showBootMenu();
	//std::cout << "booting"; threedot();
	//std::cout << "\ninitramfs"; threedot();
	//clear();
	//std::cout << "\033[32m";
	//bootanim();
	//clear();
	bool usr = false;
	std::cout << "Welcome to NINKILLos!\nWrite \'help\' for more info\n";
	while (true) {
		int mode = console();
		switch (mode) {
		case 1:
			clear();
		login:
			usr = whoiswantingin();
			if (usr == false) {
				std::cout << "Sorry... That name or password is incorect.\n";
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
			std::cout << "Rebooting"; threedot();
			clear();
			goto reboot;
			break;
		}
	}
	saveForum(FoRuM);
}