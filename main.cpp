#include "libtorrent/add_torrent_params.hpp"
#include "libtorrent/read_resume_data.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <resume-data-file>" << std::endl;
        return 1;
    }

    // Get data from resume data file
    std::ifstream ifs(argv[1], std::ios_base::binary);
    ifs.unsetf(std::ios_base::skipws);
    std::vector<char> buf{std::istream_iterator<char>(ifs)
            , std::istream_iterator<char>()};
    if (!buf.size()) {
        std::cerr << "The resume data file does not exist or is empty!" << std::endl;
        return 1;
    }

    // Read resume data and get add torrent param
    lt::add_torrent_params atp;
    try {
         atp = lt::read_resume_data(buf);
    }
    catch (boost::system::system_error){
        std::cerr << "Failed to read resume data!" << std::endl;
        return 1;
    }

    return 0;
}
