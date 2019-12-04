#include <iostream>
#include <complex>

#include "csv_parser.h"
#include "tuple_print.h"

int main() {
    std::string input_file_name = "test.csv";

    try {
        CSV_parser<std::complex<float>, std::string> parser(input_file_name);
        for(auto rs : parser){
            std::cout << rs << std::endl;
        }
    } catch (std::invalid_argument &err) {
        std::cerr << err.what() << std::endl;
    } catch (parser_exception &exception) {
        std::cerr << exception.what() << std::endl;
        return 0;
    } catch (type_mismatch &err) {
        std::cerr << err.what() << " Row: " << err.get_row() << " Column: " << err.get_column() << std::endl;
        return 0;
    }

    return 0;
}