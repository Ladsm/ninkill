#include <iostream>
#include <string>
#include <vector>
#include "usrAndPass.hpp"

std::vector<user> list = { nin ,john ,hoikgrew ,testmem ,jorin };

bool whoiswantingin() {
	std::string nameget;
	std::string passget;
	std::cout << "Normal Inside Net by Nuebine Incorperated Network\nname: ";
	std::getline(std::cin >> std::ws, nameget); std::cout << "password: ";
	std::getline(std::cin >> std::ws, passget);
	for (int i = 0; i < list.size(); i++) {
		if (nameget == list[i].name && passget == list[i].password)
		{
			return true;
		}
	}
	return false;
}