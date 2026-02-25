#pragma once
#include "obfstr.hpp"
#include <vector>
#include <string>
#include "usrAndPass.hpp"
struct reply {
    std::string paragraph = H("");
    user replyer;
    reply() = default;
    reply(std::string x, user y) {
        paragraph = x;
        replyer = y;
    }
};
struct Post {
    bool locked = false;
    std::string title = H("DEBUG");
    user poster;
    std::vector<reply> replies;
    Post() = default;
    Post(std::string x, user y, std::vector<reply> z) {
        title = x;
        poster = y;
        replies = z;
        if (locked == true) {
            title.append(H(" [LOCKED] "));
        }
    }
    Post(std::string x, user y, std::vector<reply> z, bool f) {
        title = x;
        poster = y;
        replies = z;
        locked = f;
    }
};
struct Page {
    std::string title;
    std::vector<Post> posts;;
    Page(std::string x, std::vector<Post> z) {
        title = x;
        posts = z;
    }
};
