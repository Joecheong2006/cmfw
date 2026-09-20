add_executable(demo
    src/main.c
    src/game_test.c
)
target_compile_definitions(demo PUBLIC PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/")
target_link_libraries(demo PRIVATE CMFW_LIB)
