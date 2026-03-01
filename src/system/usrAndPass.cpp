#include <util/obfstr.hpp>
#include <system/usrAndPass.hpp>
#include <iostream>
#include <string>
#include <vector>

extern std::vector<user> list;
user currentuser;
bool whoiswantingin() {
	std::string nameget;
	std::string passget;
	std::cout << H("Normal Inside Net by Nuebine Incorperated Network\nIf you only want to view the site and not post, use the name BANDIT and password ENVELOPE\nname: ");
	std::getline(std::cin >> std::ws, nameget); std::cout << H("password: ");
	std::getline(std::cin >> std::ws, passget);
	if (nameget == H("BANDIT") && passget == H("ENVELOPE")) {
		currentuser.name = "BANDIT";
		currentuser.level = 0;
		return true;
	}
	for (int i = 0; i < list.size(); i++) {
		if (nameget == list[i].name && passget == list[i].password)
		{
			currentuser = list[i];
			return true;
		}
	}
	return false;
}