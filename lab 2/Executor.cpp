//
// Created by Admin on 29.10.2019.
//
#include "Parser.h"
#include "Blocks.h"
#include "Executor.h"

Executor::Executor(Parser *currParser) {
    workflow = currParser;
}

void Executor::CheckBlocksOrder(std::string &order) {
    if (order.size() == 1) {
        if (!isdigit(order[0])) {
            throw std::ios_base::failure("No order of blocks.");
        }
        commandsOrder.push_back(atoi(&order[0]));
    }

    unsigned int countNodes = 0;
    auto pos = order.find("->", 0);
    while (pos != std::string::npos) {
        countNodes++;
        pos = order.find("->", pos + 1);
    }

    unsigned int countCommands = 0;
    for (char &i : order) {
        if (isdigit(i)) {
            countCommands++;
            commandsOrder.push_back(atoi(&i));
        }
    }

    if (countNodes != countCommands - 1)
        throw std::ios_base::failure("Incorrect order of blocks. Problems with nodes.");
}

int Executor::ExecuteWork() {
    std::vector<std::string> tmpText;

    try {
        CheckBlocksOrder(workflow->order);
    } catch (std::exception &err) {
        std::cerr << "Error:" << err.what() << std::endl;
        return -1;
    }


    for (unsigned long i = 0; i < commandsOrder.size(); i++) {
        auto it = workflow->argumentsOfCommand.find(commandsOrder[i]);

        auto currBlock = BlockFactory::Instance().Create(it->second);
        if (currBlock == nullptr)
            throw std::invalid_argument("Unexpected command.");

        if (i == 0 && currBlock->ReturnBlockType() != in)
            throw std::logic_error("Incorrect order.");

        if (i == commandsOrder.size() - 1 && currBlock->ReturnBlockType() != out)
            throw std::logic_error("Incorrect order.");

        if (currBlock->ReturnBlockType() != in_out && (i > 0 && i < commandsOrder.size() - 1))
            throw std::logic_error("Incorrect order.");

        try {
            tmpText = currBlock->DoCommand(tmpText);
        } catch (std::exception &err) {
            throw std::ios_base::failure(err.what());
        }
    }
    return 0;
}