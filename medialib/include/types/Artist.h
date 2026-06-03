#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace welle::medialib::types {
    struct Artist {
        int64_t albumCount;
        std::string artistImageUrl;
        std::string coverArt;
        std::string id;
        std::string name;
        std::vector<std::string> roles;
        std::string sortName;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Artist, albumCount, artistImageUrl, coverArt, id, name, roles, sortName)
}