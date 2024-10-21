cmake_minimum_required(VERSION 3.22)
project(assembly_projects)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCES ${SOURCE_DIR}/*.asm ${SOURCE_DIR}/*.s)

foreach(source_file IN LISTS SOURCES)
    get_filename_component(SOURCE_FILE_NAME ${source_file} NAME_WE)

    add_executable(${SOURCE_FILE_NAME} ${source_file} )

    target_link_options(${SOURCE_FILE_NAME} PRIVATE -T ${DEFAULT_ASM_LINKERFILE})

    add_custom_command(
        TARGET ${SOURCE_FILE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${SOURCE_FILE_NAME}> ${BIN_DIR}/${SOURCE_FILE_NAME}.bin
        COMMENT "Generating binary"
    )

    add_custom_command(
        TARGET ${SOURCE_FILE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:${SOURCE_FILE_NAME}> > ${OBJDUMP_DIR}/${SOURCE_FILE_NAME}.dump
        COMMENT "Generating object dump"
    )

    add_custom_target(build_${SOURCE_FILE_NAME} ALL
        DEPENDS ${SOURCE_FILE_NAME}
        DEPENDS ${BIN_DIR}/${SOURCE_FILE_NAME}.bin
        DEPENDS ${OBJDUMP_DIR}/${SOURCE_FILE_NAME}.dump
    )
endforeach()
