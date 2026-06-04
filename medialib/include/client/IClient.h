#pragma once

#include <string>
#include <vector>

#include "types/Song.h"
#include "types/Album.h"

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
        virtual std::vector<types::Artist> getArtists(TSearchParameters searchParameters = {}) = 0;
        virtual std::vector<types::Album> getAlbums(TSearchParameters searchParameters = {}) = 0;

        virtual void downloadCoverArt(const types::Song &song) = 0;
    };
}