#include <iostream>
#include <algorithm>
#include "Reader.h"
#include "Writer.h"

using namespace std;

int main(int argc, char **argv) {
    setlocale(LC_ALL, "rus");

    Reader reader;
    Writer writer;

    if (argc != 3) {
        std::cout << "Invalid count of arguments";
        exit(1);
    }

    try {
        reader.openFile(argv[1]);
    } catch(const char *error) {
        std::cout << "Couldn't open input file " << error << std::endl;
    }

    try {
        writer.openFile(argv[2]);
    } catch(const char *error) {
        std::cout << "Couldn't open output file " << error << std::endl;
    }

    writer.printCSV(reader.fillMap());

    //system("pause");
    return 0;
}
