set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Quick
        REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(Welle
        src/main.cpp
)

qt_add_qml_module(Welle
        URI welle
        VERSION 1.0
        QML_FILES
            qml/Main.qml
)

target_link_libraries(Welle PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        medialib
)

set_property(TARGET Welle PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Welle PRIVATE -O2)
    set_property(TARGET Welle PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    target_link_options(Welle PRIVATE -Wl,--strip-all)
endif()