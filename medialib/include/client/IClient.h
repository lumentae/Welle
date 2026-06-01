#pragma once

class IClient {
public:
    virtual ~IClient() = default;

    virtual std::string performRequest(std::string url) = 0;

    virtual void ping() = 0;

    virtual void getSongs() = 0;
    virtual void getArtists() = 0;
    virtual void getAlbums() = 0;
};