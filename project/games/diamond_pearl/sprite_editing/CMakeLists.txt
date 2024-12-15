cmake_minimum_required(VERSION 3.22)
project(sprite_editing)

set(SUB_SPRITE_PROJECTS
set_sprite_hooks
    inject_custom_sprite
    load_sprite_from_narc
    inject_custom_palette
)

foreach(SUB_SPRITE_PROJECT IN LISTS SUB_SPRITE_PROJECTS)
    set(SUB_SPRITE_DIR ${SUB_DIR})
    set(BIN_DIR ${SUB_SPRITE_DIR}/bin)
    set(OBJDUMP_DIR ${SUB_SPRITE_DIR}/dump)

    add_custom_target(make_${GAME}_${SUB_SPRITE_PROJECT}_dirs ALL)

    add_custom_command(TARGET make_${GAME}_${SUB_SPRITE_PROJECT}_dirs PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SUB_SPRITE_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJDUMP_DIR}
        COMMENT "Creating directories for subproject: ${SUB_SPRITE_PROJECT}"
    )

    add_subdirectory(${SUB_SPRITE_PROJECT})
endforeach()