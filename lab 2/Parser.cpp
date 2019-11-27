//
// Created by Admin on 29.10.2019.
//

#include "Parser.h"

int Parser::CheckCurrBlock(std::string &blockDef) {
    int idN = 0;
    if (isdigit(blockDef[0])) {
        char num = blockDef[0];
        idN = atoi(&num);

        try {
            if (idN < 0) {
                throw std::invalid_argument("Number of block can't be a negative number.");
            }
        } catch (std::exception &err) {
            std::cerr << "Error:" << err.what() << std::endl;
            return 1;
        }
    }

    try {
        if (!isdigit(blockDef[0]) || (blockDef[2] != '='))
            throw std::invalid_argument("Number of block doesn't exist.");
    } catch (std::exception &err) {
        std::cerr << "Error:" << err.what() << std::endl;
        return 1;
    }

    auto it = argumentsOfCommand.find(idN);
    try {
        if (it != argumentsOfCommand.end())
            throw std::ios_base::failure("Numbers of blocks cannot be repeated.");
    } catch (std::exception &err) {
        std::cerr << "Error:" << err.what() << std::endl;
        return 1;
    }

    std::list<std::string> currArguments;
    int j = 0;
    std::string currWord;
    char symbol;

    for (unsigned long i = 4; i < blockDef.size(); i++) {
        symbol = blockDef[i];
        if (symbol != ' ') {
            currWord.insert(j, 1, symbol);
            j++;
        } else {
            if (!currWord.empty()) {
                currArguments.push_back(currWord);
                j = 0;
                currWord.clear();
            }
        }
    }

    if (!currWord.empty()) {
        currArguments.push_back(currWord);
        currWord.clear();
    }

    argumentsOfCommand.insert(std::pair<int, std::list<std::string>>(idN, currArguments));
    return 0;
}

int Parser::ReadScheme(std::string &workflowName) {
    workflowFile.open(workflowName);

    if (!workflowFile.is_open()) {
        throw std::ios_base::failure("File doesn't exist.");
    }

    std::string currSchemeStr;
    while (getline(workflowFile, currSchemeStr)) {
        bool isOpenWord = false;
        if (currSchemeStr == "desc") {
            isOpenWord = true;
            bool isCloseWord = false;

            while (currSchemeStr != "csed" && !workflowFile.eof()) {
                getline(workflowFile, currSchemeStr);

                if (currSchemeStr == "csed") {
                    isCloseWord = true;
                } else {
                    try {
                        CheckCurrBlock(currSchemeStr);
                    } catch (std::exception &err) {
                        throw std::ios_base::failure(err.what());
                    }
                }
            }

            if (!isCloseWord) {
                throw std::ios_base::failure("No key word for end of blocks definition.");
            }
        }
        if (!isOpenWord)
            throw std::ios_base::failure("No key word for beginning of blocks definition.");

        if (!getline(workflowFile, currSchemeStr)) {
            throw std::ios_base::failure("No structure of scheme.");
        }
        order = currSchemeStr;
    }

    workflowFile.close();
    return 0;
}


