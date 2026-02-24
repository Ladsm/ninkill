#include "ninkill.hpp"

//users
user nin = user("nin", "XxAdMiN123xX", 4);
user john = user("john", "12345678910mod", 3);
user Ladsm = user("Ladsm", "no...youarenotgetingmypassword", 3);
user hoikgrew = user("hoikgrew", "HoknGrew", 3);
user testmem = user("TEST", "TESTSTART", 1);
user jorin = user("jorin", "dfsjhjiof", -1);
//replies
reply one = reply("After two years of work, fun and more. The Ninkill forums is shuting down.", nin);
reply two = reply("Im done with the harasment, you assholes cant dox me and expect me to continue running this shit", nin);
//posts
std::vector<reply> NINKILLPinnedarr = { one };
Post NINKILLPinned = Post("PINNED Ninkill is takeing a break", nin, NINKILLPinnedarr);
std::vector<reply> Imsickarr = { two };
Post Imsick = Post("Im sick of this", nin, Imsickarr);
//pages
std::vector<Post> indexarr = { NINKILLPinned, Imsick };
Page Index = Page{ "Index", indexarr };
std::vector<Page> FoRuM = { Index };
std::vector<user> list = { nin ,john ,hoikgrew ,testmem ,jorin };

void init() {
	//users
	nin = user("nin", "XxAdMiN123xX", 4);
	john = user("john", "12345678910mod", 3);
	Ladsm = user("Ladsm", "no...youarenotgetingmypassword", 3);
	hoikgrew = user("hoikgrew", "HoknGrew", 3);
	testmem = user("TEST", "TESTSTART", 1);
	jorin = user("jorin", "dfsjhjiof", -1);
	list = { nin ,john ,hoikgrew ,testmem ,jorin };
	//replies
	one = reply("After two years of work, fun and more. The Ninkill forums is shuting down.", nin);
	two = reply("Im done with the harasment, you assholes cant dox me and expect me to continue running this shit", nin);
	//posts
	NINKILLPinnedarr = { one };
	NINKILLPinned = Post("PINNED Ninkill is takeing a break", nin, NINKILLPinnedarr);
	Imsickarr = { two };
	Imsick = Post("Im sick of this", nin, Imsickarr);
	//pages
	indexarr = { NINKILLPinned, Imsick };
	Index = Page{ "Index", indexarr };
	FoRuM = { Index };
}

int main() {
	init();
	/*
	//start
	std::cout << "booting"; threedot();
	std::cout << "\ninitramfs"; threedot();
	cls();
	std::cout << "\033[32m";
	bootanim();
	cls();
	console();
	cls();
	login:
	bool usr = whoiswantingin();
	if (usr == false) {
		std::cout << "Sorry... That name or password is incorect.\n";
		goto login;
	}
	*/
	initforum();
	//real forum
	forum(FoRuM);
}