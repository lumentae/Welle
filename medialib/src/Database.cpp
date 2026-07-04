#include "Database.h"

#include <iostream>

namespace welle::medialib {
    void Database::init() {
        std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;

        m_Database = std::make_shared<SQLite::Database>("database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "SQLite database file '" << m_Database->getFilename().c_str() << "' opened successfully\n";
    }

    void Database::close() {
        m_Database.reset();
    }
}
