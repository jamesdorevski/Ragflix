cmake_minimum_required(VERSION 3.27)
project(Ragflix VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LibtorrentRasterbar REQUIRED)

add_executable(Ragflix main.cpp)

target_link_libraries(Ragflix PRIVATE LibtorrentRasterbar::torrent-rasterbar)