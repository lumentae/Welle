FetchContent_Declare(
        quickdigest5
        GIT_REPOSITORY https://github.com/nthnn/QuickDigest5
        GIT_TAG v1.0
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/quickdigest5
)
FetchContent_MakeAvailable(quickdigest5)

add_library(quickdigest5 STATIC
    quickdigest5/src/quickdigest5.cpp
    quickdigest5/include/quickdigest5.hpp
)

target_include_directories(quickdigest5 PUBLIC quickdigest5/include)
set_target_properties(quickdigest5 PROPERTIES POSITION_INDEPENDENT_CODE ON)