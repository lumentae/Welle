#pragma once
#include <string>
#include <nlohmann/json.hpp>

#include "Artist.h"

namespace welle::medialib::types {
    struct Genre {
        std::string name;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Genre, name);

    struct Album {
        std::string artist;
        std::string artistId;
        std::vector<Artist> artists;
        std::string coverArt;
        std::string created;
        std::vector<nlohmann::json> discTitles;
        std::string displayArtist;
        int64_t duration;
        std::string explicitStatus;
        std::string genre;
        std::vector<Genre> genres;
        std::string id;
        bool isCompilation;
        std::vector<nlohmann::json> moods;
        std::string musicBrainzId;
        std::string name;
        nlohmann::json originalReleaseDate;
        int64_t playCount;
        std::string played;
        std::vector<nlohmann::json> recordLabels;
        nlohmann::json releaseDate;
        std::vector<nlohmann::json> releaseTypes;
        int64_t songCount;
        std::string sortName;
        int64_t userRating;
        std::string version;
        int64_t year;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Album, artist, artistId, artists, coverArt, created, discTitles, displayArtist, duration, explicitStatus, genre, genres, id, isCompilation, moods, musicBrainzId, name, originalReleaseDate, playCount, played, recordLabels, releaseDate, releaseTypes, songCount, sortName, userRating, version, year)
}
