#include <iostream>
#include "Parser.h"
#include "Executor.h"

int main(int argc, char **argv) {
    try {
        if (argc < 2)
            throw std::invalid_argument("No workflow file!");
    } catch (std::exception &err) {
        std::cerr << "Error:" << err.what() << std::endl;
        return 0;
    }
    std::string workflowName = argv[1];

    Parser newWorkflow;
    try {
        newWorkflow.ReadScheme(workflowName);
    } catch (std::exception &err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 0;
    }

    Executor currExecutor(&newWorkflow);
    try {
        currExecutor.ExecuteWork();
    } catch (std::exception &err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 0;
    }

    std::cout << "Program ends successfully." << std::endl;
    return 0;
}
