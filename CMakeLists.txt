cmake_minimum_required(VERSION 3.26)
project(dfs_cilent)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc/)
add_executable(dfs_cilent
        src/dfs_client.cpp
        src/util.cpp
        src/debug.cpp
        src/system.cpp
        src/threadpool.cpp
        src/unisock.cpp
        main.cpp
        src/dfs_client.cpp)
