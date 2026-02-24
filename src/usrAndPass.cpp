#include <iostream>
#include <string>
#include <vector>
#include "usrAndPass.hpp"
bool BANDIT = false;
extern std::vector<user> list;
bool whoiswantingin() {
	std::string nameget;
	std::string passget;
	std::cout << "Normal Inside Net by Nuebine Incorperated Network\nIf you only want to view the site and not post, use the name BANDIT and password ENVELOPE\nname: ";
	std::getline(std::cin >> std::ws, nameget); std::cout << "password: ";
	std::getline(std::cin >> std::ws, passget);
	if (nameget == "BANDIT" && passget == "ENVELOPE") {
		BANDIT = true;
		return true;
	}
	for (int i = 0; i < list.size(); i++) {
		if (nameget == list[i].name && passget == list[i].password)
		{
			return true;
		}
	}
	return false;
}