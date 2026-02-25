#include "obfstr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#ifdef _WIN32
#include <shlobj.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif
#include "page.hpp"

namespace fs = std::filesystem;

void caesarCipher(std::string& data, int shift = 3) {
    for (char& c : data) {
        if (c >= 32 && c <= 126) {
            c = 32 + (c - 32 + shift + 95) % 95;
        }
    }
}

std::string getAppDataPath() {
    std::string path;
#ifdef _WIN32
    PWSTR pszPath = NULL;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath))) {
        std::wstring ws(pszPath);
        path = std::string(ws.begin(), ws.end());
        CoTaskMemFree(pszPath);
    }
#elif defined(__linux__)
    const char* home = std::getenv(H("HOME"));
    if (!home) {
        home = getpwuid(getuid())->pw_dir;
    }
    if (home) {
        path = std::string(home) + H("/.local/share");
    }
#endif
    return path;
}

void saveForum(const std::vector<Page>& pages) {
    std::string baseDir = getAppDataPath();
    fs::path filePath = fs::path(baseDir) / H("NINKILL") / H("NINKILLforumdata.bin");
    fs::create_directories(filePath.parent_path());
    std::string data;
    for (const auto& page : pages) {
        data += H("PAGE|") + page.title + H("\n");
        for (const auto& post : page.posts) {
            data += H("POST|") + post.title + H("|") + post.poster.name + H("\n");

            for (const auto& rep : post.replies) {
                data += H("REPLY|") + rep.replyer.name + H("|") + rep.paragraph + H("\n");
            }
        }
    }
    caesarCipher(data, 3);
    std::ofstream out(filePath, std::ios::binary);
    out << data;
}
std::vector<Page> loadForum(const std::vector<user>& users) {
    std::vector<Page> pages;
    std::string baseDir = getAppDataPath();
    fs::path filePath = fs::path(baseDir) / H("NINKILL") / H("NINKILLforumdata.bin");
    std::ifstream in(filePath, std::ios::binary);
    if (!in.is_open())
        return pages;
    std::string data((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    caesarCipher(data, -3);
    std::istringstream stream(data);
    std::string line;
    Page* currentPage = nullptr;
    Post* currentPost = nullptr;
    while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        std::string type;
        std::getline(linestream, type, '|');
        if (type == H("PAGE")) {
            std::string title;
            std::getline(linestream, title);
            pages.emplace_back(title, std::vector<Post>{});
            currentPage = &pages.back();
        }
        else if (type == H("POST") && currentPage) {
            std::string title, posterName;
            std::getline(linestream, title, '|');
            std::getline(linestream, posterName);
            user poster;
            for (const auto& u : users)
                if (u.name == posterName)
                    poster = u;
            currentPage->posts.emplace_back(title, poster, std::vector<reply>{});
            currentPost = &currentPage->posts.back();
        }
        else if (type == H("REPLY") && currentPost) {
            std::string name, paragraph;
            std::getline(linestream, name, '|');
            std::getline(linestream, paragraph);

            user replyUser;
            for (const auto& u : users)
                if (u.name == name)
                    replyUser = u;

            currentPost->replies.emplace_back(paragraph, replyUser);
        }
    }
    return pages;
}
bool loadForumIfExists(const std::vector<user>& users, std::vector<Page>& pages) {
    std::string baseDir = getAppDataPath();

    fs::path filePath = fs::path(baseDir) / H("NINKILL") / H("NINKILLforumdata.bin");
    if (!fs::exists(filePath))
        return false;
    pages = loadForum(users);
    return true;
}