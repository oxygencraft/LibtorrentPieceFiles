#ifndef LIBTORRENTPIECEFILES_MAIN_H
#define LIBTORRENTPIECEFILES_MAIN_H

#include "libtorrent/torrent_flags.hpp"

#include <string>
#include <vector>

lt::torrent_flags_t originalFlags;

std::vector<char> readFile(char* fileName);
char askQuestion(std::string question, std::vector<char> answers);
void setFlag(lt::torrent_flags_t flag, bool value, lt::torrent_flags_t& flags);
bool getFlag(lt::torrent_flags_t flag, lt::torrent_flags_t& flags);

#endif //LIBTORRENTPIECEFILES_MAIN_H
