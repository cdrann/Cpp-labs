//
// Created by Admin on 10.09.2019.
//

#include "Reader.h"
#include <iostream>

int Reader::openFile(const char *filein) {
    fin.open(filein);
    if (fin.good()) {
        return 0;
    }
    return 1;
}

std::map <std::string, int> Reader::fillMap() {
    while(fin.good()) {
        std::string buff;
        std::string currStr;
        getline(fin, buff);

        for (char i : buff) {
            if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i >= '0' && i <= '9')) {
                currStr += i;
            }
            else if (!currStr.empty()) {
                words[currStr]++;
                currStr = "";
            }
        }

        if(!currStr.empty()) {
            words[currStr]++;
            currStr = "";
        }
    }
    return words;
}

Reader::~Reader() {
    fin.close();
}