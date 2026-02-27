#pragma once
#include "obfstr.hpp"
#include <string>
#include <functional>
void mkbg();
using RouteTable = std::unordered_map<std::string, std::function<void()>>;
RouteTable buildRouter();