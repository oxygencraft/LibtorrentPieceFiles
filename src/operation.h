#ifndef LIBTORRENTPIECEFILES_OPERATION_H
#define LIBTORRENTPIECEFILES_OPERATION_H

#include "libtorrent/add_torrent_params.hpp"

class operation {
    public:
        virtual void execute(lt::add_torrent_params atp, char* pieceFile[], lt::torrent_flags_t originalFlags) = 0;
};


#endif //LIBTORRENTPIECEFILES_OPERATION_H
