#pragma once
#include <string>
#include <utility>

#include "IClient.h"

namespace welle::medialib {
    class SubsonicClient : public IClient {
    public:
        explicit SubsonicClient(std::string serverUrl, std::string username, std::string password) :
            m_ServerUrl(std::move(serverUrl)),
            m_Password(std::move(password)),
            m_Username(std::move(username)) {}

        std::string performRequest(std::string endpoint) override;

        void ping() override;

        void getSongs() override;
        void getArtists() override;
        void getAlbums() override;

    private:
        static std::string generateSalt(int length);

        std::string m_ServerUrl;
        std::string m_Password;
        std::string m_Username;
    };
}
