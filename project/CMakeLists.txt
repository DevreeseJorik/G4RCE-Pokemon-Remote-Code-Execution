cmake_minimum_required(VERSION 3.22)
project(project_builder)

enable_language(ASM)

set(OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)

set(GAMES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/games)
set(GAME_NAMES diamond_pearl platinum heartgold_soulsilver)

add_custom_target(make_output_dirs ALL)

foreach(GAME ${GAME_NAMES})
    set(GAME_OUT_DIR ${OUT_DIR}/${GAME})
    set(GAME_PROJECT_DIR ${GAMES_DIR}/${GAME})

    add_custom_command(TARGET make_output_dirs PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GAME_OUT_DIR}
        COMMENT "Creating directories for game: ${GAME}"
    )

    add_subdirectory(${GAME_PROJECT_DIR})
endforeach()

add_custom_target(project_builder ALL DEPENDS make_output_dirs)
