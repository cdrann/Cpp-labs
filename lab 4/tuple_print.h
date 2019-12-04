//
// Created by Admin on 01.12.2019.
//

#ifndef CSVPARSER_TUPLE_PRINT_H
#define CSVPARSER_TUPLE_PRINT_H

#include <tuple>
#include <fstream>
#include <iostream>

template <typename Tuple, unsigned N, unsigned Size>
struct tuple_print {
    static void print(std::ostream& out, const Tuple& tuple) {
        out << "\"" << std::get<N>(tuple) << "\";";
        tuple_print<Tuple, N + 1, Size>::print(out, tuple);
    }
};

template <typename Tuple, unsigned N>
struct tuple_print<Tuple, N, N> {
    static void print(std::ostream& out, const Tuple& tuple) {
        out << "\"" << std::get<N>(tuple) << "\";";
    }
};

template <typename Tuple, unsigned N>
struct tuple_print<Tuple, N, 0> {
    static void print(std::ostream& out, const Tuple& tuple) {}
};

template <typename...Argc>
auto & operator<<(std::ostream &out, const std::tuple<Argc...>& arg) {
    tuple_print<std::tuple<Argc...>, 0, sizeof...(Argc) - 1>::print(out, arg);
    return out;
}

#endif //CSVPARSER_TUPLE_PRINT_H
