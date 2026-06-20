#include <iostream>
#include <random>
#include <client/OpenSubsonicClient.h>

#include "quickdigest5.hpp"
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

namespace welle::medialib::client {
    std::string OpenSubsonicClient::generateSalt(const int length = 6) {
        static const std::string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, chars.size() - 1);

        std::string salt;
        salt.reserve(length);
        for (int i = 0; i < length; i++)
            salt += chars[dist(gen)];

        return salt;
    }

    nlohmann::json OpenSubsonicClient::search3(OpenSubsonicSearchParameters searchParameters) {
        if (searchParameters.query.empty())
            searchParameters.query = "\"\"";

        const nlohmann::json response = nlohmann::json::parse(performRequest("search3", {
            {"query", searchParameters.query},
            {"artistCount", std::to_string(searchParameters.artistCount)},
            {"artistOffset", std::to_string(searchParameters.artistOffset)},
            {"albumCount", std::to_string(searchParameters.albumCount)},
            {"albumOffset", std::to_string(searchParameters.albumOffset)},
            {"songCount", std::to_string(searchParameters.songCount)},
            {"songOffset", std::to_string(searchParameters.songOffset)},
        }));

        return response;
    }

    std::string OpenSubsonicClient::performRequest(const std::string endpoint, const std::vector<cpr::Parameter> parameters = {}) {
        const std::string salt = generateSalt();
        auto requestParameters = cpr::Parameters{
            {"u", m_Username},
            {"t", QuickDigest5::toHash(m_Password + salt)},
            {"s", salt},
            {"v", "1.16.1"},
            {"c", "Welle"},
            {"f", "json"},
        };

        for (const auto& parameter: parameters) {
            requestParameters.Add(parameter);
        }

        cpr::Response r = cpr::Get(cpr::Url{m_ServerUrl + "/rest/" + endpoint},
            requestParameters
        );

        return r.text;
    }

    void OpenSubsonicClient::ping() {
        const nlohmann::json response = nlohmann::json::parse(performRequest("ping.view"));
        std::cout << response.dump(4) << std::endl;
    }

    std::vector<types::Song> OpenSubsonicClient::getSongs(const OpenSubsonicSearchParameters searchParameters) {
        const nlohmann::json response = search3(searchParameters);
        const auto songs = response["subsonic-response"]["searchResult3"]["song"].get<std::vector<types::Song>>();
        for (auto& song : songs) {
            downloadCoverArt(song);
        }

        return songs;
    }

    std::vector<types::Artist> OpenSubsonicClient::getArtists(const OpenSubsonicSearchParameters searchParameters) {
        const nlohmann::json response = search3(searchParameters);
        return response["subsonic-response"]["searchResult3"]["artist"].get<std::vector<types::Artist>>();
    }

    std::vector<types::Album> OpenSubsonicClient::getAlbums(const OpenSubsonicSearchParameters searchParameters) {
        const nlohmann::json response = search3(searchParameters);
        return response["subsonic-response"]["searchResult3"]["album"].get<std::vector<types::Album>>();
    }

    void OpenSubsonicClient::downloadCoverArt(const types::Song &song) {
        // TODO: submit this to background thread
        if (!std::filesystem::exists({"cache"}))
            std::filesystem::create_directory({"cache"});

        const auto cachePath = std::filesystem::path("cache/" + song.coverArt);
        if (std::filesystem::exists(cachePath))
            return;

        const auto response = performRequest("getCoverArt.view",
            {
                {"id", song.coverArt}
            });
        std::ofstream(cachePath, std::ios::binary) << response;
    }

    void OpenSubsonicClient::downloadSong(const types::Song &song) {
        if (!std::filesystem::exists({"songs"}))
            std::filesystem::create_directory({"songs"});

        const auto cachePath = std::filesystem::path("songs/" + song.id + "." + song.suffix);
        if (std::filesystem::exists(cachePath))
            return;

        const auto response = performRequest("download",
            {
                {"id", song.id}
            });
        std::ofstream(cachePath, std::ios::binary) << response;
    }
}
