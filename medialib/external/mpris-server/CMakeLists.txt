FetchContent_Declare(
        sdbus
        GIT_REPOSITORY https://github.com/Kistler-Group/sdbus-cpp
        GIT_TAG master
)
FetchContent_Declare(
        mpris-server
        GIT_REPOSITORY https://codeberg.org/chrg/mpris-server.git
        GIT_TAG master
)
FetchContent_MakeAvailable(sdbus mpris-server)

add_library(mpris-server INTERFACE)
target_include_directories(mpris-server INTERFACE
        ${mpris-server_SOURCE_DIR}/src
)
target_link_libraries(mpris-server INTERFACE
        sdbus-c++
)