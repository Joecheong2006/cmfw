cmake_minimum_required(VERSION 3.14)
project(CMFW LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(lib/glad)
add_subdirectory(lib/stb_image)
add_subdirectory(src)

add_subdirectory(testing)
