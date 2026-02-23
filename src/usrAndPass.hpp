#pragma once
#include <iostream>

struct user {
	std::string name;
	std::string password;
	int level;
	user(std::string x, std::string y, int z) { name = x; password = y; level = z; }
};
/*
* levels:
* 1. member
* 2. staff
* 3. moderator
* 4. admin
* -1. banned
*/
bool whoiswantingin();