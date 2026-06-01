#include <iostream>
#include <random>
#include <client/SubsonicClient.h>
#include <cpr/cpr.h>

#include "quickdigest5.hpp"

namespace welle::medialib {
    std::string SubsonicClient::generateSalt(const int length = 6) {
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

    std::string SubsonicClient::performRequest(const std::string endpoint) {
        const std::string salt = generateSalt();
        cpr::Response r = cpr::Get(cpr::Url{m_ServerUrl + "/rest/" + endpoint},
                      cpr::Parameters{
                          {"u", m_Username},
                          {"t", QuickDigest5::toHash(m_Password + salt)},
                          {"s", salt},
                          {"v", "1.16.1"},
                          {"c", "Welle"},
                          {"f", "json"},
                      });
        return r.text;
    }

    void SubsonicClient::ping() {
        const std::string response = performRequest("ping.view");
        std::cout << response << std::endl;
    }

    void SubsonicClient::getSongs() {
    }

    void SubsonicClient::getArtists() {
    }

    void SubsonicClient::getAlbums() {
    }
}
