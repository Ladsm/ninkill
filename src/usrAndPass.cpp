#include <iostream>
#include <string>
#include <vector>
#include <src/usrAndPass.hpp>

user nin      = user("nin", "XxAdMiN123xX", 4);
user john     = user("john", "12345678910mod", 3);
user Ladsm    = user("Ladsm", "no...youarenotgetingmypassword", 3);
user hoikgrew = user("hoikgrew", "HoknGrew", 3);
user testmem  = user("TEST", "TESTSTART", 1);
user jorin    = user("jorin", "dfsjhjiof", -1);

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