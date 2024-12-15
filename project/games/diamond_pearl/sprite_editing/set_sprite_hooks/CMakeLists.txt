cmake_minimum_required(VERSION 3.22)
project(set_sprite_hooks)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(set_sprite_hooks ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(set_sprite_hooks PRIVATE ${COMMON_LIB_DIR})

set_target_properties(set_sprite_hooks PROPERTIES
    LINK_FLAGS "-T${DEFAULT_C_LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET set_sprite_hooks POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:set_sprite_hooks> ${BIN_DIR}/set_sprite_hooks.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET set_sprite_hooks POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:set_sprite_hooks> > ${OBJDUMP_DIR}/set_sprite_hooks.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_set_sprite_hooks ALL
    DEPENDS set_sprite_hooks
    DEPENDS ${BIN_DIR}/set_sprite_hooks.bin
    DEPENDS ${OBJDUMP_DIR}/set_sprite_hooks.dump
)
