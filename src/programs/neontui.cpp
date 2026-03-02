#include <programs/api.hpp>

std::vector<std::string> itemsz(std::vector<package> pkgs) {
	std::vector<std::string> itemz;
	for (size_t i = 0; i < pkgs.size(); i++) {
		if (pkgs[i].willDownload == true && pkgs[i].hidden == false) {
			itemz.push_back(pkgs[i].name);
		}
	}
	return itemz;
}
int installremovepkg(std::vector<package> pkgs, int wheareq) {
	if (pkgs[wheareq].downloaded == false) {
		pkgs[wheareq].downloaded = true;
		return 20;
	}
	else {
		pkgs[wheareq].downloaded = false;
		return 5;
	}
}
void neontui() {
	std::vector<std::string> items = itemsz(packagesz);
}