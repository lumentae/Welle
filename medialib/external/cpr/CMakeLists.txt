set(CURL_LIBCURL_VERSIONED_SYMBOLS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG f091b2c061b307ee89b164c39976fc9202a1c79d # 1.14.2
)
FetchContent_MakeAvailable(cpr)