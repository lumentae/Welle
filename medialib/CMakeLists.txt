add_subdirectory(external)

add_library(medialib SHARED
        src/client/SubsonicClient.cpp
        include/client/SubsonicClient.h
        include/client/IClient.h
)

target_link_libraries(medialib PUBLIC
        cpr::cpr
        nlohmann_json::nlohmann_json
        quickdigest5
)

target_include_directories(medialib PUBLIC include)