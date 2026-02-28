#pragma once
#include <string>
#include <vector>
struct VNode {
	std::string name;
	bool isDir;
	std::string content;
	bool isExec = false;
	std::function<int(const std::vector<std::string>&)> execFunc;
	VNode* parent = nullptr;
	std::unordered_map<std::string, std::unique_ptr<VNode>> children;
	bool locked = false;
	std::string passwordHash;
	VNode(std::string n, bool d, VNode* p = nullptr)
		:name(std::move(n)), isDir(d), parent(p) {
	}
};
int console();
void initFS();
int readKey();
VNode* mkdirNode(VNode* parent, const std::string& name);
VNode* mkfile(VNode* parent, const std::string& name, const std::string& txt);
VNode* resolvePath(const std::string& path);
std::string cwdPath();
std::string getcommand();
std::vector<std::string> tokenize(const std::string& line);
void listdir();
void printDevices();
void EXIT(int code);
int readcommand(const std::string& line);
