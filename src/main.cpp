#include "util.h"

#include "libtorrent/torrent_info.hpp"
#include "libtorrent/add_torrent_params.hpp"
#include "libtorrent/read_resume_data.hpp"

#include <iostream>
#include <vector>

lt::torrent_flags_t originalFlags;

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <resume-data-file> <torrent-file> <piece-file.pieces>" << std::endl;
        return 1;
    }

    // Get data from resume data file
    std::vector<char> buf = readFile(argv[1]);
    if (!buf.size()) {
        std::cerr << "The resume data file does not exist or is empty!" << std::endl;
        return 1;
    }

    std::cout << "Loading resume data..." << std::endl;

    // Read resume data and get add torrent param
    lt::add_torrent_params atp;
    try {
         atp = lt::read_resume_data(buf);
    } catch (boost::system::system_error e) {
        std::cerr << "Failed to read resume data!" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Check if the resume data includes torrent info, if not try to retrieve it
    if (atp.ti == NULL && argc < 4) {
        std::cerr << "Torrent info does not exist in resume data, please specify torrent file!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <resume-data-file> <piece-file.pieces> <torrent-file>" << std::endl;
        return 1;
    } else if (atp.ti == NULL) {
        std::cout << "Torrent info does not exist in resume data, loading torrent file..." << std::endl;

        std::vector<char> buf = readFile(argv[2]);
        if (!buf.size()) {
            std::cerr << "Torrent file does not exist or is empty!" << std::endl;
            return 1;
        }

        try {
            atp.ti = std::make_shared<lt::torrent_info>(buf, lt::from_span);
        } catch (boost::system::system_error e) {
            std::cerr << "Failed to read torrent file!" << std::endl;
            std::cerr << e.what() << std::endl;
        }


        if (atp.ti->info_hash() != atp.info_hash) {
            std::cerr << "Torrent file info does not match resume data info" << std::endl;
            return 1;
        }
    }

    // Check if paused and set flags and store them if we save the resume data
    originalFlags = atp.flags;
    if (!getFlag(lt::torrent_flags::paused, atp.flags)) {
        std::cerr << "Please pause the torrent before continuing." << std::endl;
        return 1;
    }
    setFlag(lt::torrent_flags::auto_managed, false, atp.flags);
    setFlag(lt::torrent_flags::need_save_resume, false, atp.flags);

    // Get answers from user
    char answer;
    // We need to check again in case the resume data hasn't been saved while its running yet
    answer = askQuestion("Are you sure that the torrent is paused?", {'y', 'n'});
    if (answer != 'y') {
        std::cerr << "Please pause the torrent before continuing." << std::endl;
        return 1;
    }
    bool importing;
    answer = askQuestion("Import or export pieces?", {'i', 'e'});
    if (answer == 'i')
        importing = true;
    else
        importing = false;

    // Run the operations
    if (!importing) {
        bool deletePieces;
        if (atp.ti->num_files() > 1) {
            deletePieces = false;
            std::cout << "Please note that deleting pieces on torrents with more than one file is not supported." << std::endl;
            answer = askQuestion("Do you still wish to continue?", {'y', 'n'});
            if (answer == 'n')
                return 0;
        } else {
            answer = askQuestion("Delete pieces?", {'y', 'n'});
            if (answer == 'y')
                deletePieces = true;
            else
                deletePieces = false;
        }

        // Run export pieces operation
    } else {
        // Run import pieces operation
    }


    return 0;
}