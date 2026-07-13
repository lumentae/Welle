#include "Database.h"

#include <iostream>

#include "types/Song.h"

namespace welle::medialib {
    void Database::init() {
        std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;

        m_Database = std::make_shared<SQLite::Database>("database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "SQLite database file '" << m_Database->getFilename().c_str() << "' opened successfully\n";

        m_Database->exec(R"(
            CREATE TABLE IF NOT EXISTS songs (
                album TEXT,
                albumId TEXT,
                artist TEXT,
                artistId TEXT,
                bitrate INT,
                coverArt TEXT,
                created DATETIME,
                duration INT,
                genre TEXT,
                id TEXT PRIMARY KEY,
                path TEXT,
                playCount INT,
                played DATETIME,
                samplingRate INT,
                size INT,
                suffix TEXT,
                title TEXT,
                year INT
            )
        )");

        m_Database->exec(R"(
            CREATE TABLE IF NOT EXISTS artists (
                albumCount INT,
                artistImageUrl TEXT,
                coverArt TEXT,
                id TEXT PRIMARY KEY,
                name TEXT
            )
        )");

        m_Database->exec(R"(
            CREATE TABLE IF NOT EXISTS albums (
                artist TEXT,
                artistId TEXT,
                coverArt TEXT,
                created DATETIME,
                duration INT,
                genre TEXT,
                id TEXT PRIMARY KEY,
                name TEXT,
                playCount INT,
                played DATETIME,
                songCount INT,
                userRating INT,
                version TEXT,
                year INT
            )
        )");

        m_Database->exec(R"(
            CREATE TABLE IF NOT EXISTS playlists (
                id TEXT PRIMARY KEY,
                name TEXT,
                owner TEXT,
                created DATETIME,
                changed DATETIME,
                songCount INT,
                duration INT
            )
        )");
    }

    void Database::insertSongs(const std::vector<types::Song> &songs) const {
        for (auto& song : songs) {
            SQLite::Statement statement(*m_Database, R"(
                INSERT OR IGNORE INTO songs
                VALUES (
                    :album,
                    :albumId,
                    :artist,
                    :artistId,
                    :bitrate,
                    :coverArt,
                    :created,
                    :duration,
                    :genre,
                    :id,
                    :path,
                    :playCount,
                    :played,
                    :samplingRate,
                    :size,
                    :suffix,
                    :title,
                    :year
                )
            )");
            statement.bind(":album", song.album);
            statement.bind(":albumId", song.albumId);
            statement.bind(":artist", song.artist);
            statement.bind(":artistId", song.artistId);
            statement.bind(":bitrate", song.bitrate);
            statement.bind(":coverArt", song.coverArt);
            statement.bind(":created", song.created);
            statement.bind(":duration", song.duration);
            statement.bind(":genre", song.genre);
            statement.bind(":id", song.id);
            statement.bind(":path", song.path);
            statement.bind(":playCount", song.playCount);
            statement.bind(":played", song.played);
            statement.bind(":samplingRate", song.samplingRate);
            statement.bind(":size", song.size);
            statement.bind(":suffix", song.suffix);
            statement.bind(":title", song.title);
            statement.bind(":year", song.year);
            statement.exec();
        }
    }

    std::vector<types::Song> Database::getSongs() const {
        SQLite::Statement statement(*m_Database, R"(
            SELECT * FROM songs
        )");

        std::vector<types::Song> songs;
        while (statement.executeStep()) {
            types::Song song {
                .album = statement.getColumn(0).getString(),
                .albumId = statement.getColumn(1).getString(),
                .artist = statement.getColumn(2).getString(),
                .artistId = statement.getColumn(3).getString(),
                .bitrate = statement.getColumn(4).getUInt(),
                .coverArt = statement.getColumn(5).getString(),
                .created = statement.getColumn(6).getString(),
                .duration = statement.getColumn(7).getUInt(),
                .genre = statement.getColumn(8).getString(),
                .id = statement.getColumn(9).getString(),
                .path = statement.getColumn(10).getString(),
                .playCount = statement.getColumn(11).getUInt(),
                .played = statement.getColumn(12).getString(),
                .samplingRate = statement.getColumn(13).getUInt(),
                .size = statement.getColumn(14).getUInt(),
                .suffix = statement.getColumn(15).getString(),
                .title = statement.getColumn(16).getString(),
                .year = statement.getColumn(17).getInt(),
            };
            songs.push_back(song);
        }
        return songs;
    }

    // TODO: insert plalylist songs into db somehow
    void Database::insertPlaylists(const std::vector<types::Playlist> &playlists) const {
        for (const auto& playlist : playlists) {
            SQLite::Statement statement(*m_Database, R"(
                INSERT OR IGNORE INTO playlists
                VALUES (
                    :id,
                    :name,
                    :owner,
                    :created,
                    :changed,
                    :songCount,
                    :duration
                )
            )");
            statement.bind(":id", playlist.id);
            statement.bind(":name", playlist.name);
            statement.bind(":owner", playlist.owner);
            statement.bind(":created", playlist.created);
            statement.bind(":changed", playlist.changed);
            statement.bind(":songCount", playlist.songCount);
            statement.bind(":duration", playlist.duration);
            statement.exec();
        }
    }

    std::vector<types::Playlist> Database::getPlaylists() const {
        SQLite::Statement statement(*m_Database, R"(
            SELECT * FROM playlists
        )");

        std::vector<types::Playlist> playlists;
        while (statement.executeStep()) {
            types::Playlist playlist {
                .id = statement.getColumn(0).getString(),
                .name = statement.getColumn(1).getString(),
                .owner = statement.getColumn(2).getString(),
                .created = statement.getColumn(3).getString(),
                .changed = statement.getColumn(4).getString(),
                .songCount = statement.getColumn(5).getUInt(),
                .duration = statement.getColumn(6).getUInt(),
            };
            playlists.push_back(playlist);
        }
        return playlists;
    }

    void Database::close() {
        m_Database.reset();
    }
}
