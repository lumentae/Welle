#pragma once

#include "IClient.h"

namespace welle::medialib {
    struct OpenSubsonicSearchParameters {
        std::string query = "\"\"";
        uint32_t artistCount = 20;
        uint32_t artistOffset = 0;
        uint32_t albumCount = 20;
        uint32_t albumOffset = 0;
        uint32_t songCount = 20;
        uint32_t songOffset = 0;
    };

    class OpenSubsonicClient : public IClient<OpenSubsonicSearchParameters> {
    public:
        using SearchParameters = OpenSubsonicSearchParameters;

        explicit OpenSubsonicClient(std::string serverUrl, std::string username, std::string password) :
            m_ServerUrl(std::move(serverUrl)),
            m_Password(std::move(password)),
            m_Username(std::move(username)) {}

        std::string performRequest(std::string endpoint, std::vector<cpr::Parameter> parameters) override;

        void ping() override;

        void getSongs(OpenSubsonicSearchParameters searchParameters = {}) override;
        void getArtists() override;
        void getAlbums() override;

    private:
        static std::string generateSalt(int length);

        std::string m_ServerUrl;
        std::string m_Password;
        std::string m_Username;
    };
}
