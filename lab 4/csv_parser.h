//
// Created by Admin on 01.12.2019.
//

#ifndef CSVPARSER_CSV_PARSER_H
#define CSVPARSER_CSV_PARSER_H

#include <vector>
#include <sstream>

#include "parser_error.h"
#include "tuple_fill.h"
#include "tuple_print.h"

std::vector<std::string> divideString(std::string &str, char column_delimiter) {
    std::vector<std::string> result;
    size_t k = 0;
    size_t i;

    std::string sub_str;

    for(i = 0; i < str.length();i++) {
        if(str[i] == column_delimiter) {
            result.push_back(str.substr(i - k, k));
            k = 0;
        } else {
            k++;
        }
    }

    if(k > 0) {
        result.push_back(str.substr(i - k, k));
    }
    return result;
}


template <typename ... Args>
class CSV_parser {
private:
    std::string input_file_name;
    char delimiter;
public:
    CSV_parser(std::string name, char character = ';') : input_file_name(name), delimiter(character) {
        //verify file existence
        std::ifstream in;
        in.open(input_file_name);
        if(!in.is_open()) {
            throw std::invalid_argument("File can't be open.");
        }
        in.close();
    }

    class CSVIterator{
    private:
        std::ifstream file;
        size_t index;
        char delimiter;
        std::tuple<Args...> tuple;
        std::string name;
    public:
        CSVIterator(const std::string name_of_input, size_t ind, char character) {
            index = ind;
            delimiter = character;
            name = name_of_input;
            file.open(name_of_input);

            int curr_row = -1;
            std::string curr_str;
            std::vector<std::string> vector_of_str;
            std::tuple<Args...> curr_tuple;

            if(index >= 0) {
                while(std::getline(file, curr_str)) {
                    curr_row++;
                    if(curr_row == index){
                        vector_of_str = divideString(curr_str, delimiter);
                        if(vector_of_str.size() != sizeof...(Args))
                            throw parser_exception("Invalid number of parameters in line.");

                        makeTuple<Args...>(curr_tuple, vector_of_str, curr_row);
                        tuple = curr_tuple;
                        break;
                    }
                }

                if(curr_row == -1) {
                    index = -1;
                }
            }

        }

        CSVIterator &operator++() {
            index++;

            std::string curr_str;
            std::vector<std::string> vector_of_str;
            std::tuple<Args...> curr_tuple;

            if(std::getline(file, curr_str)) {
                vector_of_str = divideString(curr_str, delimiter);
                if(vector_of_str.size() != sizeof...(Args))
                    throw parser_exception("Invalid number of parameters in line.");

                makeTuple<Args...>(curr_tuple, vector_of_str, index);
                tuple = curr_tuple;
            } else {
                index = -1;
                file.close();
            }

            return *this;
        }


        std::tuple<Args...> operator*() const {
            return tuple;
        }

        std::tuple<Args...>* operator->() const {
            return &tuple;
        }

        friend bool operator==(const CSVIterator & first, const CSVIterator& second) {
            return (first.index == second.index);
        }

        friend bool operator!=(const CSVIterator &first, const CSVIterator &second) {
            return !(first == second);
        }
    };

    CSVIterator begin()const {
        return CSVIterator(input_file_name, 0, delimiter);
    }

    CSVIterator end()const {
        return CSVIterator(input_file_name, -1, delimiter);
    }
};

#endif //CSVPARSER_CSV_PARSER_H
