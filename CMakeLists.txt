cmake_minimum_required(VERSION 3.1)
project(AYKVMSBB C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    main.c rodata.h util.h subroutines.h)

add_executable(aykvmsbb ${SOURCE_FILES})
