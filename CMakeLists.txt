cmake_minimum_required(VERSION 3.20)
project(Ragflix VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    libtorrent
    GIT_REPOSITORY https://github.com/arvidn/libtorrent.git
    GIT_TAG 74bc93a37a5e31c78f0aa02037a68fb9ac5deb41
)
FetchContent_MakeAvailable(libtorrent)

add_executable(Ragflix main.cpp)
target_link_libraries(Ragflix PRIVATE torrent-rasterbar)