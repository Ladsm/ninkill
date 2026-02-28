#include <string>
#include <functional>
struct SysCommand {
    std::string name;
    std::function<int(const std::vector<std::string>&)>action;
};
extern std::unordered_map<std::string, SysCommand> sysCommands;
void initSysCommands();
int nin_sys_cmd(const std::vector<std::string>& args);