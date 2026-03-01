#pragma once
#include <util/obfstr.hpp>
#include <iostream>

struct user {
	std::string name = H("Deleted");
	std::string password = H("-");
	int level = 1;
	user() = default;
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
extern user currentuser;
bool whoiswantingin();