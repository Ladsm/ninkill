#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <map>
struct VNode {
	std::string name;
	bool isDir;
	std::string content;
	bool isExec = false;
	std::function<int(const std::vector<std::string>&)> execFunc;
	VNode* parent = nullptr;
	std::map<std::string, std::unique_ptr<VNode>> children;
	bool locked = false;
	std::string passwordHash;
	VNode(std::string n, bool d, VNode* p = nullptr)
		:name(std::move(n)), isDir(d), parent(p) {
	}
};
std::string cwdPath();
VNode* mkdirNode(VNode* parent, const std::string& name);
VNode* mkfile(VNode* parent, const std::string& name, const std::string& txt);
VNode* resolvePath(const std::string& path);
std::string hashPass(const std::string& s);
void lockDir(VNode* dir, const std::string& pass);
bool unlockDir(VNode* dir, const std::string& attempt);
extern std::unique_ptr<VNode> root;
extern VNode* cwd;
void mkuserfiles(VNode* dir);
void initFS();
void wipeFS();
extern VNode* tmpDir;