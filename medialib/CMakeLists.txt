add_subdirectory(external)

add_library(medialib STATIC
        include/Queue.h
        include/audio/AudioPlayer.h
        include/audio/MprisServer.h
        include/client/IClient.h
        include/client/OpenSubsonicClient.h
        include/types/Album.h
        include/types/Artist.h
        include/types/Song.h
        include/utility/String.h
        src/Queue.cpp
        src/audio/AudioPlayer.cpp
        src/audio/MprisServer.cpp
        src/client/OpenSubsonicClient.cpp
        src/Database.cpp
        include/Database.h
)

target_link_libraries(medialib PUBLIC
        cpr::cpr
        nlohmann_json::nlohmann_json
        quickdigest5
        miniaudio
        miniaudio_libopus
        mpris-server
        SQLiteCpp
        sqlite3
)

target_include_directories(medialib PUBLIC include)