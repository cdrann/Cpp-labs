#ifndef LAB_1_1_TRAITSET_H
#define LAB_1_1_TRAITSET_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

enum Trit { False, Unknown, True }; // 01 00 10

class Trit_set {
public:
    //Вложенный класс Reference
    class Reference {
        friend class Trait_set;
    private:
        Trit_set *trit_set; //TODO shared/unique ptr?
        int index_trit; //Индекс текущего трита
    public:
        Reference(Trit_set *curr_trit_set, int index);
        Reference& operator=(Trit val);
        Reference& operator=(const Reference& ref);
        operator Trit () const;
        friend std::ostream& operator<< (std::ostream& out, const Reference& ref);
    };

private:
    int capacity;
public:
    std::vector<unsigned char> set; //TODO все поля класса должны быть приватными !! try to make 'em private and check if it works
    int size_of_set; //TODO все поля класса должны быть приватными !!

    //Методы основного класса
    Trit_set(int size);

    //Оператор индексации
    Reference operator[] (int trit_index);
    Trit operator[] (int trit_index)const;

    //Конструктор копирования
    Trit_set(const Trit_set &trit_set);

    //Логические операторы для тритсетов
    Trit_set operator |(const Trit_set &set_2);
    Trit_set operator &(const Trit_set &set_2);
    Trit_set operator ~();

    //Опреатор присваивания всему тритсету(задать начальное значение для всех тритов)
    Trit_set& operator =(Trit def_value);

    //Освободить память до последнего установленного трита
    void Shrink();

    //Вернуть вместимость тритсета
    int Capacity();

    //Вернуть размер тритсета
    int Size();

    //Число установленных в данное значение тритов
    unsigned int Cardinality(Trit val);

    //Общая статистика
    std::unordered_map<Trit , int> Cardinality();

    //Опреатор вывода трита
    friend std::ostream& operator<<(std::ostream& out, Trit_set &set);

    //Забыть содержимое от last index и дальше
    void Trim(int last_index);

    //Логическая длинна
    unsigned int Logical_length();
};

//Оператор вывода для случая если в качетсве аргумента передается значение enum
std::ostream& operator<<(std::ostream& out, Trit val);

#endif