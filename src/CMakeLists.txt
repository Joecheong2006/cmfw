# glfw cglm sndfile openal
find_package(glfw3 CONFIG REQUIRED)
find_package(SndFile REQUIRED)
find_package(OpenAL REQUIRED)

# --- OPENAL MAC VS WINDOWS FIX ---
if(APPLE)
    # Force CMake to read Homebrew's openal-soft package instead of Apple's SDK
    find_package(PkgConfig REQUIRED)
    set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/opt/homebrew/opt/openal-soft/lib/pkgconfig:/usr/local/opt/openal-soft/lib/pkgconfig")
    pkg_check_modules(OPENAL REQUIRED openal)
else()
    # Windows/vcpkg route
    find_package(OpenAL REQUIRED)
endif()

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

# Standard Libraries
target_link_libraries(CMFW_LIB PUBLIC
    glfw
    glad
    stb_image
    SndFile::sndfile
)

# Conditional OpenAL Application
if(APPLE)
    target_include_directories(CMFW_LIB PUBLIC ${OPENAL_INCLUDE_DIRS} /opt/homebrew/include /usr/local/include)
    target_link_libraries(CMFW_LIB PUBLIC ${OPENAL_LIBRARIES})
else()
    target_link_libraries(CMFW_LIB PUBLIC OpenAL::OpenAL Winmm)
endif()

# Conditional CGLM Application
find_package(cglm QUIET)
if(cglm_FOUND)
    target_link_libraries(CMFW_LIB PUBLIC cglm::cglm)
else()
    if(NOT PkgConfig_FOUND)
        find_package(PkgConfig REQUIRED)
    endif()
    pkg_check_modules(CGLM REQUIRED cglm)
    
    target_include_directories(CMFW_LIB PUBLIC ${CGLM_INCLUDE_DIRS})
    target_link_libraries(CMFW_LIB PUBLIC ${CGLM_LIBRARIES})
endif()

target_include_directories(CMFW_LIB PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)
target_compile_definitions(CMFW_LIB PUBLIC CMFW_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/../")
