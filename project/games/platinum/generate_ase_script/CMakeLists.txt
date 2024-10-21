cmake_minimum_required(VERSION 3.22)
project(generate_ase_script_${GAME})

find_package(Python3 REQUIRED)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCES ${SOURCE_DIR}/*.asm ${SOURCE_DIR}/*.s)

add_custom_target(generate_ase_script_${GAME} ALL)

foreach(source_file IN LISTS SOURCES)
    get_filename_component(FILE_NAME ${source_file} NAME_WE)
    set(FILE_TARGET_NAME ${GAME}_${FILE_NAME})

    add_executable(${FILE_TARGET_NAME} ${source_file} )

    target_link_options(${FILE_TARGET_NAME} PRIVATE -T ${DEFAULT_ASM_LINKERFILE})

    add_custom_command(
        TARGET ${FILE_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${FILE_TARGET_NAME}> ${BIN_DIR}/${FILE_NAME}.bin
        COMMENT "Generating binary"
    )

    add_custom_command(
        TARGET ${FILE_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:${FILE_TARGET_NAME}> > ${OBJDUMP_DIR}/${FILE_NAME}.dump
        COMMENT "Generating object dump"
    )

    add_custom_target(build_${FILE_TARGET_NAME} ALL
        DEPENDS ${FILE_TARGET_NAME}
        DEPENDS ${BIN_DIR}/${FILE_NAME}.bin
        DEPENDS ${OBJDUMP_DIR}/${FILE_NAME}.dump
    )

    add_dependencies(generate_ase_script_${GAME} build_${FILE_TARGET_NAME})
endforeach()

add_custom_command(
    TARGET generate_ase_script_${GAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running generate_script.py"
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_script.py
        --bin-path ${BIN_DIR}
        --base-script-path ${CMAKE_CURRENT_SOURCE_DIR}/data/base_script.json
        --output-script-path ${SUB_DIR}/script.json
        --game ${GAME}
    COMMENT "Running generate_script.py to generate the final script"
)
