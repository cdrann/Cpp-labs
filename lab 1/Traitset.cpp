#include "Traitset.h"
#include "Trait_operations.h"

//Конструктор
Trit_set::Trit_set(int size) {
    size_of_set = size;
    if(size_of_set < 0)
        throw std::invalid_argument("Size cannot be negative");
    if(size_of_set <= 4 && size_of_set > 0) {
        capacity = 1;
        set.resize(capacity);
    } else {
        if(size % 4 == 0) {
            if(size == 0) {
                capacity = 0;
                set.resize(capacity);
            } else {
                capacity = size / 4;
                set.resize(capacity);
            }
        } else {
            capacity = size / 4 + 1;
            set.resize(capacity);
        }
    }
}

//Опреатор индексации
Trit_set::Reference Trit_set::operator[](int trit_index) {
    if(trit_index < 0)
        throw std::invalid_argument("Index cannot be negative");
    return Reference(this, trit_index);
}

Trit Trit_set::operator[](int trit_index) const {
    if(trit_index < 0)
        throw std::invalid_argument("Index cannot be negative");
    return Get_Trait_value(this->set, trit_index % 4, trit_index, size_of_set);
}

//Конструктор копирования
Trit_set::Trit_set(const Trit_set &trit_set) {
    set = trit_set.set;
    size_of_set = trit_set.size_of_set;
    capacity = trit_set.capacity;
}

//Логические операции
//Логическое ИЛИ
Trit_set Trit_set::operator|(const Trit_set &set_2) {
    int max_size = 0;
    if(this->size_of_set >= set_2.size_of_set) {
        max_size = size_of_set;
    } else {
        max_size = set_2.size_of_set;
    }

    Trit_set resultSet(max_size);
    Trit value_1;
    Trit value_2;

    for(int i = 0; i < max_size; i++) {
        value_1 = (*this)[i];
        value_2 = set_2[i];
        resultSet[i] = value_1 | value_2;
    }
    return resultSet;
}

//Логическое И
Trit_set Trit_set::operator&(const Trit_set &set_2) {
    int max_size = 0;
    if(this->size_of_set >= set_2.size_of_set) {
        max_size = size_of_set;
    } else {
        max_size = set_2.size_of_set;
    }

    Trit_set resultSet(max_size);
    Trit value_1;
    Trit value_2;

    for(int i = 0; i < max_size; i++) {
        value_1 = (*this)[i];
        value_2 = set_2[i];
        resultSet[i] = value_1 & value_2;
    }
    return resultSet;
}

//Логическое НЕ
Trit_set Trit_set::operator~() {
    Trit_set resultSet(size_of_set);
    Trit value;
    for(int i = 0; i < size_of_set; i++) {
        value = Get_Trait_value(this->set, i % 4, i, this->size_of_set);
        resultSet[i] = ~(value);
    }
    return resultSet;
}

//Опреатор присваивания
Trit_set& Trit_set::operator=(Trit def_value) {
    for(int i = 0; i < size_of_set; i++) {
        Set_Trait(set, i % 4, i, def_value);
    }
    return *this;
}

//Освобождение памяти до последнего установленного значения трита
void Trit_set::Shrink() {
    int index_exist = 0;
    Trit curr_trait;
    for(int i = 0; i < this->size_of_set; i++) {
        curr_trait = (*this)[i];
        if(curr_trait != Unknown) {
            index_exist = i;
        }
    }

    if(index_exist < this->size_of_set - 1) {
        if(index_exist < 4) {
            this->capacity = 1;
        } else {
            if(index_exist % 4 == 0) {
                this->capacity = index_exist / 4 + 1;
            } else {
                this->capacity = (int) ceil((double) index_exist / 4);
            }
        }
        this->size_of_set = index_exist + 1;
        this->set.resize(this->capacity);
    }
}

//Вернуть значение capacity
int Trit_set::Capacity() {
    return capacity;
}

//Вернуть значение size
int Trit_set::Size() {
    return size_of_set;
}

//Число установленных в данное значение трит
unsigned int Trit_set::Cardinality(Trit val) {
    Trit curr_val;
    unsigned int stat = 0;
    for(int i = 0; i < this->size_of_set; i++) {
        curr_val = (*this)[i];
        if(curr_val == val) {
            stat++;
        }
    }
    return stat;
}

//Общая статистика cardinality
std::unordered_map<Trit , int> Trit_set::Cardinality() {
    std::unordered_map<Trit,int> stat;
    stat[False] = 0;
    stat[True] = 0;
    stat[Unknown] = 0;
    Trit curr_value;
    for(int i = 0; i < this->size_of_set; i++) {
        curr_value = (*this)[i];
        switch (curr_value) {
            case Unknown:
                stat[Unknown]++;
                break;
            case False:
                stat[False]++;
                break;
            case True:
                stat[True]++;
                break;
        }
    }
    return stat;
}

//Оператор вывода трита
std::ostream& operator<<(std::ostream &out, Trit_set &set) {
    for(int i = 0; i < set.size_of_set; i++) {
        out << "[" << i << "]:" << set[i] << std::endl;
    }
    return out;
}

//Забыть содержимое от last_index и дальше
void Trit_set::Trim(int last_index) {
    int new_size = this->size_of_set - (this->size_of_set - last_index);
    this->size_of_set = new_size;
    if(new_size <= 4) {
        this->capacity = 1;
    }
    else {
        int new_capacity = (int)ceil((double)new_size / 4);
        this->set.resize(new_capacity);
    }
}

//Логическая длинна тритсета
unsigned int Trit_set::Logical_length() {
    unsigned int last_index = -1;
    Trit curr_val;
    for(int i = 0; i < this->size_of_set; i++) {
        curr_val = (*this)[i];
        if(curr_val != Unknown) {
            last_index = i;
        }
    }
    return last_index + 1;
}

//Reference methods
Trit_set::Reference::Reference(Trit_set *curr_trit_set, int index) {
    trit_set = curr_trit_set;
    index_trit = index;
}

//Опрератор присваивания
Trit_set::Reference& Trit_set::Reference::operator=(Trit val) {
    //Если мы вышли за пределы массива и значение не Unknown
    if((index_trit >= trit_set->size_of_set) && (val != Unknown)) {
        int new_capacity = 0;
        if(index_trit % 4 == 0 && index_trit > 4) {
            new_capacity = index_trit / 4 + 1;
        } else {
            new_capacity = (int)ceil((double)index_trit / 4);
        }
        trit_set->set.resize(new_capacity);//Расширяем вектор
        trit_set->size_of_set = index_trit + 1;
        trit_set->capacity = new_capacity;
        Set_Trait(trit_set->set, index_trit % 4, index_trit, val);
    } else {    //Если выхода за гарницы не было то добавляем в соответствующую ячейку
        Set_Trait(trit_set->set, index_trit % 4, index_trit, val);
    }
    //В противном случае ничего никуда не добавляется
    return *this;
}

Trit_set::Reference& Trit_set::Reference::operator=(const Reference &ref) {
    *this = (Trit)ref;
    return *this;
}

//Оператор приведения типов
Trit_set::Reference::operator Trit () const {
    return Get_Trait_value(trit_set->set, index_trit % 4, index_trit, trit_set->size_of_set);
}

//Оператор вывода трит
std::ostream& operator<< (std::ostream& out, const Trit_set::Reference& ref) {
    Trit val = Get_Trait_value(ref.trit_set->set, ref.index_trit % 4, ref.index_trit, ref.trit_set->size_of_set);
    /*  if(val == True) {
        out << "True";
    }
    else if(val == False) {
        out << "False";
    } else {
        out << "Unknown";
    } */
    switch(val) {
        case True:
            out << "True";
            break;
        case False:
            out << "False";
            break;
        default:
            out << "Unknown";
    }
    return out;
}

//Оператор для более удобного вывода значений enum
std::ostream& operator<<(std::ostream& out, Trit val) {
    switch(val) {
        case True:
            out << "True";
            break;
        case False:
            out << "False";
            break;
        default:
            out << "Unknown";
    }
    return out;
}