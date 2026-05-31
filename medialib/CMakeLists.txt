add_subdirectory(external)

add_library(medialib SHARED
        src/SubsonicClient.cpp
        include/SubsonicClient.h
)

target_link_libraries(medialib PUBLIC
    cpr::cpr
)

target_include_directories(medialib PUBLIC include)