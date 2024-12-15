cmake_minimum_required(VERSION 3.22)
project(load_sprite_from_narc)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(load_sprite_from_narc ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(load_sprite_from_narc PRIVATE ${COMMON_LIB_DIR})

set(LINKERFILE ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

set_target_properties(load_sprite_from_narc PROPERTIES
    LINK_FLAGS "-T${LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET load_sprite_from_narc POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:load_sprite_from_narc> ${BIN_DIR}/load_sprite_from_narc.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET load_sprite_from_narc POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:load_sprite_from_narc> > ${OBJDUMP_DIR}/load_sprite_from_narc.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_load_sprite_from_narc ALL
    DEPENDS load_sprite_from_narc
    DEPENDS ${BIN_DIR}/load_sprite_from_narc.bin
    DEPENDS ${OBJDUMP_DIR}/load_sprite_from_narc.dump
)
