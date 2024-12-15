cmake_minimum_required(VERSION 3.22)
project(inject_custom_palette)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(inject_custom_palette ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(inject_custom_palette PRIVATE ${COMMON_LIB_DIR})

set(LINKERFILE ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

set_target_properties(inject_custom_palette PROPERTIES
    LINK_FLAGS "-T${LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET inject_custom_palette POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:inject_custom_palette> ${BIN_DIR}/inject_custom_palette.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET inject_custom_palette POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:inject_custom_palette> > ${OBJDUMP_DIR}/inject_custom_palette.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_inject_custom_palette ALL
    DEPENDS inject_custom_palette
    DEPENDS ${BIN_DIR}/inject_custom_palette.bin
    DEPENDS ${OBJDUMP_DIR}/inject_custom_palette.dump
)
