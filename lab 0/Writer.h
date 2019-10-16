//
// Created by Admin on 10.09.2019.
//

#ifndef WORD_COUNT_WRITER_H
#define WORD_COUNT_WRITER_H
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

class Writer {
private:
    std::map <int, std::string> sortedList;
    std::ofstream fout;
public:
    void printCSV(std::map <std::string, int> map);
    int openFile(const char *fileout);
    ~Writer();
};


#endif
