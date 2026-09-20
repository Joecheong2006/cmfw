# glfw cglm sndfile openal
find_package(glfw3 CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)
find_package(SndFile REQUIRED)
find_package(OpenAL REQUIRED)

add_library(CMFW_LIB STATIC
    anim_duration.c
    anim_duration_system.c
    anim_position_slide.c
    audio.c
    camera.c
    camera_shake.c
    game_object_system.c
    input_system.c
    physics2d_object_system.c
    shader_program.c
    sprite.c
    stimer.c
    trace_info.c
    transform.c
    window_callback.c

    platform/platform_linux.c
    platform/platform_win32.c

    physics2d/box2d.c
    physics2d/capsule2d.c
    physics2d/circle2d.c
    physics2d/collider2d.c
    physics2d/collision2d_impl.c
    physics2d/rigid2d.c
    
    opengl/opengl_buffer_object.c

    debug/line_renderer.c
    debug/primitive_shape_renderer.c

    core/log.c

    basic/hashmap.c
    basic/memallocate.c
    basic/queue.c
    basic/string.c
    basic/vector.c
)

target_link_libraries(CMFW_LIB PUBLIC
    glfw
    glad
    stb_image
    cglm::cglm
    SndFile::sndfile
    OpenAL::OpenAL
    Winmm
)

target_include_directories(CMFW_LIB PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)
target_compile_definitions(CMFW_LIB PUBLIC CMFW_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/../")
