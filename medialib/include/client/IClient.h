#pragma once

#include <string>
#include <vector>

#include "types/Song.h"

namespace cpr {
    struct Parameter;
}

namespace welle::medialib::client {
    template<typename TSearchParameters>
    class IClient {
    public:
        virtual ~IClient() = default;

        virtual std::string performRequest(std::string url, std::vector<cpr::Parameter> parameters) = 0;

        virtual void ping() = 0;

        virtual std::vector<types::Song> getSongs(TSearchParameters searchParameters = {}) = 0;
        virtual void getArtists() = 0;
        virtual void getAlbums() = 0;
    };
}