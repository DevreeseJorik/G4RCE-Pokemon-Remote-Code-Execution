cmake_minimum_required(VERSION 3.22)
project(enable_cloning)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c )

add_executable(enable_cloning ${SOURCE} )

target_include_directories(enable_cloning PRIVATE ${COMMON_LIB_DIR})

set_target_properties(enable_cloning PROPERTIES
    LINK_FLAGS "-T${DEFAULT_C_LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET enable_cloning POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:enable_cloning> ${BIN_DIR}/enable_cloning.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET enable_cloning POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:enable_cloning> > ${OBJDUMP_DIR}/enable_cloning.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_enable_cloning ALL
    DEPENDS enable_cloning
    DEPENDS ${BIN_DIR}/enable_cloning.bin
    DEPENDS ${OBJDUMP_DIR}/enable_cloning.dump
)
