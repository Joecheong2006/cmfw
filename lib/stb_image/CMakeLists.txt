cmake_minimum_required(VERSION 3.14)
project(StbImage LANGUAGES C)

# Target the new v2 C source file
add_library(stb_image STATIC stb_image.c)
