//
// Created by Admin on 29.10.2019.
//

#ifndef LAB2_EXECUTOR_H
#define LAB2_EXECUTOR_H
#include "Parser.h"

class Executor {
private:
    Parser *workflow;
    std::deque<int> commandsOrder;
public:
    Executor(Parser *currParser);
    void CheckBlocksOrder(std::string &order);
    int ExecuteWork();
};

#endif //LAB2_EXECUTOR_H
