cmake_minimum_required(VERSION 3.11)
project(c_rl C)

set(CMAKE_C_COMPILER /usr/bin/gcc)
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/map/*.c" )

set(COMPILE_FLAGS "-Wall -Wextra -std=c99 -Werror")
include_directories(/usr/local/include/)
link_directories(/usr/local/lib/)
add_executable(c_rl ${sources})

target_link_libraries(c_rl tcod SDL2)


