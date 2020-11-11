#ifndef LIBTORRENTPIECEFILES_EXPORT_OPERATION_H
#define LIBTORRENTPIECEFILES_EXPORT_OPERATION_H

#include "operation.h"

class export_operation : operation {
    public:
        void setDeletePieces(bool value);
        void execute(lt::add_torrent_params atp, char* pieceFile[], lt::torrent_flags_t originalFlags);
    private:
        bool deletePieces;
};


#endif //LIBTORRENTPIECEFILES_EXPORT_OPERATION_H
