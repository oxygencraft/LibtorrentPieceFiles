#include "util.h"

#include <iostream>
#include <fstream>

std::vector<char> readFile(char* fileName) {
    std::ifstream ifs(fileName, std::ios_base::binary);
    ifs.unsetf(std::ios_base::skipws);
    std::vector<char> buf{std::istream_iterator<char>(ifs)
            , std::istream_iterator<char>()};
    return buf;
}

char askQuestion(std::string question, std::vector<char> answers) {
    bool firstTime = true;
    std::string answersList = "[";
    for (char &answer : answers) {
        if (!firstTime)
            answersList += "/";
        answersList += answer;
        firstTime = false;
    }
    answersList += "] ";

    while (true) {
        std::cout << question << " " << answersList;
        char answer;
        std::cin >> answer;
        for (auto answers : answers) {
            if (tolower(answer) == tolower(answers))
                return static_cast<char>(tolower(answer));
        }
        std::cout << "Invalid answer!" << std::endl;
    }
}

void setFlag(lt::torrent_flags_t flag, bool value, lt::torrent_flags_t& flags) {
    if (value)
        flags |= flag;
    else
        flags &= ~flag;
}

bool getFlag(lt::torrent_flags_t flag, lt::torrent_flags_t& flags) {
    if (flag & flags)
        return true;
    return false;
}