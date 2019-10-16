//
// Created by Admin on 10.09.2019.
//

#ifndef WORD_COUNT_READER_H
#define WORD_COUNT_READER_H
#include <string>
#include <fstream>
#include <map>

class Reader {
private:
    std::map <std::string, int> words;
    std::ifstream fin;
public:
    int openFile(const char *fin); // fin === name of file
    std::map <std::string, int> fillMap(); //fills a map with strings from fin and returns the map
    ~Reader();
};

#endif
