#pragma once
#include "obfstr.hpp"
#include <string>
#include <functional>
struct website {
	std::string Address = H("");
	std::function<void()> siteAction;
	website() = default;
	website(std::string x, std::function<void()> y) {
		Address = x;
		siteAction = y;
	}
};
void mkbg();
extern website Nuebinedotcom;
extern website jackwddotcom;