cmake_minimum_required(VERSION 3.22)
project(async_frame)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 包含头文件所在目录
include_directories("./")

file(GLOB_RECURSE SOURCES "async/*.cpp" "frame/*.cpp" "routine/*.cpp" "socket/*.cpp" "utility/*.cpp")

add_executable(routine_test "routine/routine.cpp" routine_test.cpp)
add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)

