set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Welle
        src/main.cpp
)

target_link_libraries(Welle
        Qt::Core
        Qt::Gui
        Qt::Widgets
        medialib
)

