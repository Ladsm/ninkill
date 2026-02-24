#include "ninkill.hpp"
#include "boot.hpp"
#include "consolestart.hpp"
#include "savefile.hpp"
#include <filesystem>

//users
user nin = user("nin", "XxAdMiN123xX", 4);
user john = user("john", "12345678910mod", 3);
user Ladsm = user("Ladsm", "no...youarenotgetingmypassword", 3);
user hoikgrew = user("hoikgrew", "HoknGrew", 3);
user testmem = user("TEST", "TESTSTART", 1);
user jorin = user("jorin", "dfsjhjiof", -1);
//replies
reply Gone1 = reply("After two years of work, fun and more. The Ninkill forums is shuting down.", nin);
reply Gtwo = reply("Im done with the harasment, you assholes can’t dox me and expect me to continue running this shit", nin);
reply Nthree = reply("Nuebine incorporated Network is releaseing a new version of NINKILL!!!What do you want us to add? Because I may add them >:).", Ladsm);
reply Gone2 = reply("What? why? This is dumb, dont let the words of shity people stop your fun.", Ladsm);
//posts
std::vector<reply> NINKILLOSNEWarr = { Nthree };
Post NINKILLOSNEW = Post("NINKILL v1.3 releaseing!", Ladsm, NINKILLOSNEWarr);
std::vector<reply> NINKILLPinnedarr = { Gone1, Gone2 };
Post NINKILLPinned = Post("PINNED Ninkill is takeing a break", nin, NINKILLPinnedarr, true);
std::vector<reply> Imsickarr = { Gtwo };
Post Imsick = Post("Im sick of this", nin, Imsickarr, true);
//pages
std::vector<Post> indexarr = { NINKILLPinned, Imsick };
std::vector<Post> Newsarr = { NINKILLOSNEW };
Page News = Page{ "News", Newsarr };
Page Index = Page{ "Index", indexarr };
std::vector<Page> FoRuM = { Index, News };
std::vector<user> list = { nin ,john ,hoikgrew ,testmem ,jorin };
void init() {
	nin = user("nin", "XxAdMiN123xX", 4);
	john = user("john", "12345678910mod", 3);
	Ladsm = user("Ladsm", "no...youarenotgetingmypassword", 3);
	hoikgrew = user("hoikgrew", "HoknGrew", 3);
	testmem = user("TEST", "TESTSTART", 1);
	jorin = user("jorin", "dfsjhjiof", -1);
	list = { nin ,john ,hoikgrew ,testmem ,jorin };
}
void initForumData(const std::vector<user>& users, const std::vector<Page>& pages) {
	list = users;
	FoRuM = pages;
}
int main() {
	if (!loadForumIfExists(list, FoRuM)) {
		initForumData(list, FoRuM);
		saveForum(FoRuM);
	}
	FoRuM = loadForum(list);
	init();
	std::cout << "booting"; threedot();
	std::cout << "\ninitramfs"; threedot();
	cls();
	std::cout << "\033[32m";
	bootanim();
	cls();
	consolefirst();
	cls();
	login:
	bool usr = whoiswantingin();
	if (usr == false) {
		std::cout << "Sorry... That name or password is incorect.\n";
		goto login;
	}
	while (true) {
		initforum();
		forum(FoRuM);
#if defined(_WIN32)
		system("cls");
#endif
#if defined(__linux__)
		system("clear");
#endif
		console();
	}
	saveForum(FoRuM);
}