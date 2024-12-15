cmake_minimum_required(VERSION 3.22)
project(inject_custom_sprite)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(inject_custom_sprite ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(inject_custom_sprite PRIVATE ${COMMON_LIB_DIR})

set(LINKERFILE ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

set_target_properties(inject_custom_sprite PROPERTIES
    LINK_FLAGS "-T${LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET inject_custom_sprite POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:inject_custom_sprite> ${BIN_DIR}/inject_custom_sprite.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET inject_custom_sprite POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:inject_custom_sprite> > ${OBJDUMP_DIR}/inject_custom_sprite.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_inject_custom_sprite ALL
    DEPENDS inject_custom_sprite
    DEPENDS ${BIN_DIR}/inject_custom_sprite.bin
    DEPENDS ${OBJDUMP_DIR}/inject_custom_sprite.dump
)
