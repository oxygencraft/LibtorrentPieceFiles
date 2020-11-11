cmake_minimum_required(VERSION 3.17)
project(LibtorrentPieceFiles)

add_executable(LibtorrentPieceFiles src/main.cpp src/util.cpp src/util.h)

include(cmake/FindLibtorrentRasterbar.cmake)

#find_package(LibtorrentRasterbar REQUIRED COMPONENTS torrent-rasterbar)
target_link_libraries(LibtorrentPieceFiles PRIVATE LibtorrentRasterbar::torrent-rasterbar)