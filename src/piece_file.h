#ifndef LIBTORRENTPIECEFILES_PIECE_FILE_H
#define LIBTORRENTPIECEFILES_PIECE_FILE_H

#include <libtorrent/sha1_hash.hpp>
#include <libtorrent/units.hpp>

#include <vector>

struct piece_info {
    lt::piece_index_t piece;
    char const* data;
};

struct piece_file {
    // std::string file-format = "libtorrentpiecefile"; // It isn't used but it is there in the piece file
    lt::sha1_hash infoHash;
    // lt::sha256_hash infoHash2; // Only exists on libtorrent 2.0; we're on 1.2.10
    std::vector<piece_info> pieces;
};

#endif //LIBTORRENTPIECEFILES_PIECE_FILE_H
