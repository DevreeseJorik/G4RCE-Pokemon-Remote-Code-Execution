cmake_minimum_required(VERSION 3.22)
project(diamond_pearl)

set(COMMON_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
file(GLOB COMMON_LIB_SRC_FILES ${COMMON_LIB_DIR}/*/*.c)

set(SUB_PROJECTS
    communication
    dot_artist_editor
    assembly_projects
    generate_ase_script
    enable_cloning
    sprite_editing
)

foreach(SUB_PROJECT IN LISTS SUB_PROJECTS)
    set(SUB_DIR ${GAME_OUT_DIR}/${SUB_PROJECT})
    set(BIN_DIR ${SUB_DIR}/bin)
    set(OBJDUMP_DIR ${SUB_DIR}/dump)

    add_custom_target(make_${GAME}_${SUB_PROJECT}_dirs ALL)

    add_custom_command(TARGET make_${GAME}_${SUB_PROJECT}_dirs PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SUB_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJDUMP_DIR}
        COMMENT "Creating directories for subproject: ${SUB_PROJECT}"
    )

    add_subdirectory(${SUB_PROJECT})
endforeach()
