#ifndef LAB_1_1_TRAIT_OPERATIONS_H
#define LAB_1_1_TRAIT_OPERATIONS_H

#include "Traitset.h"

//Установить значение трита
void Set_Trait(std::vector<unsigned char> &vec_set, int position, int index_trit, Trit value);

//Получить значение трита
Trit Get_Trait_value(const std::vector<unsigned char> &vec_set, int position, int index_trit, int size_set);

//Операция логического НЕ
Trit operator ~(Trit val_1);

//Операция логического ИЛИ
Trit operator |(Trit val_1, Trit val_2);

//Операции логического И
Trit operator &(Trit val_1, Trit val_2);

#endif