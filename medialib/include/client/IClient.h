#pragma once

#include <string>
#include <vector>

namespace cpr {
    struct Parameter;
}

template<typename TSearchParameters>
class IClient {
public:
    virtual ~IClient() = default;

    virtual std::string performRequest(std::string url, std::vector<cpr::Parameter> parameters) = 0;

    virtual void ping() = 0;

    virtual void getSongs(TSearchParameters searchParameters = {}) = 0;
    virtual void getArtists() = 0;
    virtual void getAlbums() = 0;
};
