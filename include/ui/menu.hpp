#include <string>
#include <vector>
#include <functional>
bool checkfile();
void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, const std::string& title);
void MenuUse(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems);
