//
// Created by Admin on 29.10.2019.
//

#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <list>
#include <deque>

class Parser {
private:
    std::ifstream workflowFile;
    std::map<int, std::list<std::string>> argumentsOfCommand;
    std::string order;
public:
    int CheckCurrBlock(std::string &blockDef);
    int ReadScheme(std::string &workflowName);
    friend class Executor;
};

#endif //LAB2_PARSER_H
