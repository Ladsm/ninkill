#pragma once
#include <string>
#include <vector>
#include "page.hpp"
void caesarCipher(std::string& data, int shift = 3);
std::string getAppDataPath();
void saveForum(const std::vector<Page>& pages);
std::vector<Page> loadForum(const std::vector<user>& users);
bool loadForumIfExists(const std::vector<user>& users, std::vector<Page>& pages);