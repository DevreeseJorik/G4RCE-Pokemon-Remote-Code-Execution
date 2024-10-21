cmake_minimum_required(VERSION 3.22)
project(dot_artist_editor)

set(DOT_ARTIST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(dot_artist_editor ${SOURCE} )

target_include_directories(dot_artist_editor PRIVATE ${COMMON_LIB_DIR} ${DOT_ARTIST_SOURCE})

set_target_properties(dot_artist_editor PROPERTIES
    LINK_FLAGS "-T${DEFAULT_C_LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET dot_artist_editor POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:dot_artist_editor> ${BIN_DIR}/dot_artist_editor.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET dot_artist_editor POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:dot_artist_editor> > ${OBJDUMP_DIR}/dot_artist_editor.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_dot_artist_editor ALL
    DEPENDS dot_artist_editor
    DEPENDS ${BIN_DIR}/dot_artist_editor.bin
    DEPENDS ${OBJDUMP_DIR}/dot_artist_editor.dump
)
