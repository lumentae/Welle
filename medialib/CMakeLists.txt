add_subdirectory(external)

add_library(medialib STATIC
        src/client/OpenSubsonicClient.cpp
        include/client/OpenSubsonicClient.h
        include/client/IClient.h
        include/types/Song.h
)

target_link_libraries(medialib PUBLIC
        cpr::cpr
        nlohmann_json::nlohmann_json
        quickdigest5
)

target_include_directories(medialib PUBLIC include)