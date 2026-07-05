#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

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

        void insertSongs(const std::vector<types::Song> &songs) const;

        std::vector<types::Song> getSongs() const;

        void close();

    private:
        std::shared_ptr<SQLite::Database> m_Database{};
    };
}
