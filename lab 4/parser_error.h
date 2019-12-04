//
// Created by Admin on 02.12.2019.
//

#ifndef CSVPARSER_PARSER_ERROR_H
#define CSVPARSER_PARSER_ERROR_H

#include <string>
#include <utility>

class parser_exception {
private:
    std::string m_error;
public:
    explicit parser_exception(std::string error) : m_error(std::move(error)) {}
    const char* what() { return m_error.c_str();}
};

class type_mismatch {
private:
    std::string m_error;
    int curr_column;
    int curr_row;
public:
    type_mismatch(std::string error, int col, int row) :
            m_error(std::move(error)), curr_column(col), curr_row(row) {}
    const char* what(){ return m_error.c_str();}
    int get_column(){ return curr_column;}
    int get_row(){ return curr_row;}
};

#endif //CSVPARSER_PARSER_ERROR_H
