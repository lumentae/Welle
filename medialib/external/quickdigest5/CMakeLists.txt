FetchContent_Declare(
        quickdigest5
        GIT_REPOSITORY https://github.com/nthnn/QuickDigest5
        GIT_TAG main
)
FetchContent_MakeAvailable(quickdigest5)

add_library(quickdigest5 STATIC
    ${quickdigest5_SOURCE_DIR}/src/quickdigest5.cpp
    ${quickdigest5_SOURCE_DIR}/include/quickdigest5.hpp
)

target_include_directories(quickdigest5 PUBLIC ${quickdigest5_SOURCE_DIR}/include)
set_target_properties(quickdigest5 PROPERTIES POSITION_INDEPENDENT_CODE ON)