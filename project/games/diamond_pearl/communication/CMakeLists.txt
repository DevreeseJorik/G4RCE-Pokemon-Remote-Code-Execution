cmake_minimum_required(VERSION 3.22)
project(communication)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

add_executable(communication ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(communication PRIVATE ${COMMON_LIB_DIR})

set_target_properties(communication PROPERTIES
    LINK_FLAGS "-T${DEFAULT_C_LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET communication POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:communication> ${BIN_DIR}/communication.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET communication POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:communication> > ${OBJDUMP_DIR}/communication.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_communication ALL
    DEPENDS communication
    DEPENDS ${BIN_DIR}/communication.bin
    DEPENDS ${OBJDUMP_DIR}/communication.dump
)
