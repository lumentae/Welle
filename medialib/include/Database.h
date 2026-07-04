#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

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

    private:
        std::shared_ptr<SQLite::Database> m_Database{};
    };
}
