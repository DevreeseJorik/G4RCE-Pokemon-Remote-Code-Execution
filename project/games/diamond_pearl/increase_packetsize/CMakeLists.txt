cmake_minimum_required(VERSION 3.22)
project(increase_packetsize)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

add_executable(increase_packetsize ${COMMON_LIB_SRC_FILES} ${SOURCE} )

target_include_directories(increase_packetsize PRIVATE ${COMMON_LIB_DIR})

set_target_properties(increase_packetsize PROPERTIES
    LINK_FLAGS "-T${DEFAULT_C_LINKERFILE} -Wl,--just-symbols=${SYMBOLFILE}"
)

add_custom_command(
    TARGET increase_packetsize POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:increase_packetsize> ${BIN_DIR}/increase_packetsize.bin
    COMMENT "Generating binary"
)

add_custom_command(
    TARGET increase_packetsize POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:increase_packetsize> > ${OBJDUMP_DIR}/increase_packetsize.dump
    COMMENT "Generating object dump"
)

add_custom_target(build_increase_packetsize ALL
    DEPENDS increase_packetsize
    DEPENDS ${BIN_DIR}/increase_packetsize.bin
    DEPENDS ${OBJDUMP_DIR}/increase_packetsize.dump
)
