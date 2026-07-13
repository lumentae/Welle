#pragma once
#include <string>
#include <nlohmann/json.hpp>

#include "Song.h"

namespace welle::medialib::types {
    struct Playlist {
        std::string id;
        std::string name;
        std::string owner;
        std::string created;
        std::string changed;
        uint32_t songCount;
        uint32_t duration;
        std::vector<Song> entry;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Playlist, id, name, owner, created, changed, songCount, duration, entry)
}
