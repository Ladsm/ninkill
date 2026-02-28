#include <string>
#include <vector>
#include <functional>
#if defined(_WIN32)
#include <conio.h>
#endif
#if defined(__linux__)
int getch();
#endif
void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, const std::string& title);
void MenuUse(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems);
