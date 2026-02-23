#pragma once
#include <iostream>

struct user {
	std::string name;
	std::string password;
	int level;
	user(std::string x, std::string y, int z) { name = x; password = y; level = z; }
};
user nin = user("nin", "XxAdMiN123xX", 4);
user john = user("john", "12345678910mod", 3);
user Ladsm = user("Ladsm", "no...youarenotgetingmypassword", 3);
user hoikgrew = user("hoikgrew", "HoknGrew", 3);
user testmem = user("TEST", "TESTSTART", 1);
user jorin = user("jorin", "dfsjhjiof", -1);
/*
* levels:
* 1. member
* 2. staff
* 3. moderator
* 4. admin
* -1. banned
*/
bool whoiswantingin();