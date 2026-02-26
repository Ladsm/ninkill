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
using RouteTable = std::unordered_map<std::string, std::function<void()>>;
RouteTable buildRouter();