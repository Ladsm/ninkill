#include "usrAndPass.hpp"
#include "boot.hpp"
#include "consolestart.hpp"
#include "ninkill.hpp"

int main() {
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
	initforum();
}