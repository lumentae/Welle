set(ICON_NAMES
        pause
        play_arrow
)
list(JOIN ICON_NAMES "," ICON_NAMES_STRING)
file(
        DOWNLOAD
        https://fonts.googleapis.com/css2?family=Material+Symbols+Rounded:opsz,wght,FILL,GRAD@24,400,0,0&icon_names=${ICON_NAMES_STRING}
        ${CMAKE_CURRENT_SOURCE_DIR}/MaterialSymbols.ttf
)