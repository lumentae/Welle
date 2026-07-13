#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

#include "types/Playlist.h"
#include "types/Song.h"

namespace welle::medialib {
    class Database {
    public:
        Database() = default;
        static Database& getInstance() {
            static Database instance;
            return instance;
        }

        void init();
        void close();

        void insertSongs(const std::vector<types::Song> &songs) const;
        [[nodiscard]] std::vector<types::Song> getSongs() const;

        void insertPlaylists(const std::vector<types::Playlist> &playlists) const;
        [[nodiscard]] std::vector<types::Playlist> getPlaylists() const;

    private:
        std::shared_ptr<SQLite::Database> m_Database{};
    };
}
