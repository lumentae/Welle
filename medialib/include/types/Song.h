#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace welle::medialib::types {

    struct Song {
        struct Artist {
            std::string id;
            std::string name;
        };
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Artist, id, name)

        struct Genre {
            std::string name;
        };
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Genre, name)

        std::string album;
        std::vector<Artist> album_artists;
        std::string album_id;
        std::string artist;
        std::string artist_id;
        std::vector<Artist> artists;
        std::string comment;
        std::string content_type;
        std::vector<nlohmann::json> contributors;
        std::string cover_art;
        std::string created;
        std::string display_album_artist;
        std::string display_artist;
        std::string display_composer;
        int64_t duration;
        std::string genre;
        std::vector<Genre> genres;
        std::string id;
        std::string parent;
        std::string path;
        int64_t play_count;
        std::string played;
        int64_t sampling_rate;
        std::string sort_name;
        std::string suffix;
        std::string title;
        std::string type;
        int64_t year;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Song, album, album_artists, album_id, artist, artist_id, artists, comment, content_type, contributors, cover_art, created, display_album_artist, display_artist, display_composer, duration, genre, genres, id, parent, path, play_count, played, sampling_rate, sort_name, suffix, title, type, year)
}