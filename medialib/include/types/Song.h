#pragma once
#include <string>
#include <nlohmann/json.hpp>

#include "Artist.h"

namespace welle::medialib::types {
    struct Song {
        struct Genre {
            std::string name;
        };
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Genre, name)

        std::string album;
        std::vector<Artist> albumArtists;
        std::string albumId;
        std::string artist;
        std::string artistId;
        std::vector<Artist> artists;
        std::string comment;
        std::string contentType;
        std::vector<nlohmann::json> contributors;
        std::string coverArt;
        std::string created;
        std::string displayAlbumArtist;
        std::string displayArtist;
        std::string displayComposer;
        int64_t duration;
        std::string genre;
        std::vector<Genre> genres;
        std::string id;
        std::string parent;
        std::string path;
        int64_t playCount;
        std::string played;
        int64_t samplingRate;
        std::string sortName;
        std::string suffix;
        std::string title;
        std::string type;
        int64_t year;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Song, album, albumArtists, albumId, artist, artistId, artists, comment, contentType, contributors, coverArt, created, displayAlbumArtist, displayArtist, displayComposer, duration, genre, genres, id, parent, path, playCount, played, samplingRate, sortName, suffix, title, type, year)
}
