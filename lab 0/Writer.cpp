//
// Created by Admin on 10.09.2019.
//

#include "Writer.h"
#include <string>

int Writer::openFile(const char *fileout) {
    fout.open(fileout);
    if (fout.good()) {
        return 0;
    }
    return 1;
}

struct sortClassFreqAlphabet {
    bool operator() (const std::pair<std::string, int> w1, const std::pair<std::string, int> w2) {
        if (w1.second == w2.second) {
            return (w1.first < w2.first);
        }
        return (w1.second > w2.second);
    }
} sortFreqAlphabet;

void Writer::printCSV(std::map <std::string,int> map) {
    int numWords = 0;
    std::vector<std::pair<std::string,int>> dictionary(map.begin(), map.end());

    sort (dictionary.begin(), dictionary.end(), sortFreqAlphabet);

    for (auto const &pair : map) {
        numWords += pair.second;
    }

    for (int i = 0; i < dictionary.size(); i++) {
        fout << dictionary[i].first << ", " << dictionary[i].second << ", " <<
             ((double(dictionary[i].second) / numWords) * 100) << "%" << std::endl;
    }
}

Writer::~Writer() {
    fout.close();
}