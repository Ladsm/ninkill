#include <vector>
#include <string>
#include "usrAndPass.hpp"
struct reply {
    std::string paragraph = "";
    user replyer;
    reply() = default;
    reply(std::string x, user y) {
        paragraph = x;
        replyer = y;
    }
};
struct Post {
    std::string title;
    user poster;
    std::vector<reply> replies;
    Post(std::string x, user y, std::vector<reply> z) {
        title = x;
        poster = y;
        replies = z;
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
