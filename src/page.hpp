#include <vector>
#include <string>
#include "usrAndPass.hpp"
struct Post {
    std::string title;
    user poster;
    std::vector<std::string> replies;
};
struct Page {
    std::string title;
    std::vector<Post> posts;
}