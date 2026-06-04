set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Quick Qml REQUIRED)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(Welle
        src/main.cpp
)

qt_add_qml_module(Welle
        URI welle
        VERSION 1.0
        QML_FILES
            qml/Main.qml
            qml/components/SongList.qml
            qml/components/Sidebar.qml
            qml/components/SidebarEntry.qml
            qml/components/Content.qml
        qml/pages/Songs.qml
        SOURCES
            src/model/SongModel.cpp
            include/model/SongModel.h
)

target_link_libraries(Welle PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
        medialib
)
target_include_directories(Welle PUBLIC include include/model)

target_precompile_headers(Welle PRIVATE
        <QAbstractItemModel>
        <QAbstractListModel>
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Welle PRIVATE -O2)
    set_property(TARGET Welle PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    target_link_options(Welle PRIVATE -Wl,--strip-all)
endif()