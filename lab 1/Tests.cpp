#define TEST 50
//Для работы с тестами нужна main определенная в catch
#ifdef TEST
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Traitset.h"

//Проверка правильности выделения места для тритсета в зависимости от его размера
TEST_CASE("Create set") {
    Trit_set set_1(100);
    REQUIRE(set_1.Size() == 100);
    REQUIRE(set_1.Capacity() == 25);

    Trit_set set_2(4);
    REQUIRE(set_2.Size() == 4);
    REQUIRE(set_2.Capacity() == 1);

    Trit_set set_3(0);
    REQUIRE(set_3.Size() == 0);
    REQUIRE(set_3.Capacity() == 0);

    REQUIRE_THROWS_AS(Trit_set(-5), std::invalid_argument);
    REQUIRE_THROWS_AS(Trit_set(-15), std::invalid_argument);
}

//Проверка работы опреаторов и методов основного класса
TEST_CASE("Operators for Trit_set class") {
    SECTION("[]") {
        Trit_set test(5);
        test[2] = True;
        test[3] = False;
        REQUIRE(test[2] == True);
        REQUIRE(test[3] == False);
        REQUIRE(test[0] == Unknown);
        REQUIRE_THROWS_AS(test[-1], std::invalid_argument);
        REQUIRE_THROWS_AS(test[-25], std::invalid_argument);

        test[10] = Unknown;
        REQUIRE(test.Capacity() == 2);//Память не выделяется
        test[10] = True;
        REQUIRE(test.Size() == 11);//Память выделяется
        REQUIRE(test.Capacity() == 3);
        REQUIRE( test[10] == True);
        //Если обратились к неустановленным тритам
        REQUIRE(test[100] == Unknown);
    }

    SECTION("COPY") {
    Trit_set test_for_copy(5);
    Trit_set copy = test_for_copy;
    REQUIRE(copy.Size()== test_for_copy.Size());
    REQUIRE(copy.Capacity() == test_for_copy.Capacity());
    }

    SECTION("|") {
        Trit_set set_a(3);
        Trit_set set_b(4);

        set_a = True;
        set_b = False;

        Trit_set set_c = set_a | set_b;
        REQUIRE(set_c.Size() == set_b.Size());
        REQUIRE(set_c[3] == Unknown);
        REQUIRE(set_c[0] == True);
        REQUIRE(set_c[2] == True);
    }

    SECTION("&") {
        Trit_set set_AND_1(3);
        Trit_set set_AND_2(7);

        set_AND_1 = True;
        set_AND_2 = False;

        Trit_set result_of_AND = set_AND_1 & set_AND_2;
        REQUIRE(result_of_AND.Size() == set_AND_2.Size());
        REQUIRE(result_of_AND[0] == False);
        REQUIRE(result_of_AND[5] == False);
    }

    SECTION("~") {
        Trit_set set_primal(3);
        set_primal[0] = True;
        set_primal[1] = Unknown;
        set_primal[2] = False;

        Trit_set set_not = ~set_primal;
        REQUIRE(set_not[0] == False);
        REQUIRE(set_not[1] == Unknown);
        REQUIRE(set_not[2] == True);
    }

    SECTION("=") {
        Trit_set set_init(2);
        set_init = False;
        REQUIRE(set_init[0] == False);
        REQUIRE(set_init[1] == False);
        set_init = Unknown;
        REQUIRE(set_init[0] == Unknown);
        REQUIRE(set_init[1] == Unknown);
        set_init = True;
        REQUIRE(set_init[0] == True);
        REQUIRE(set_init[1] == True);
    }

    SECTION("Shrink") {
        Trit_set testSHR(10);
        testSHR[4] = True;
        testSHR.Shrink();
        REQUIRE(testSHR.Size() == 5);
        REQUIRE(testSHR.Capacity() == 2);

        Trit_set testSHR_2(5);
        testSHR_2[2] = False;
        testSHR_2.Shrink();
        REQUIRE(testSHR_2.Size() == 3);
        REQUIRE(testSHR_2.Capacity() == 1);
    }

    SECTION("Cardinality") {
        Trit_set stat_Unique(8);
        stat_Unique[0] = True;
        stat_Unique[1] = False;
        stat_Unique[5] = True;
        stat_Unique[4] = True;
        stat_Unique[8] = False;

        REQUIRE(stat_Unique.Cardinality(True) == 3);
        REQUIRE(stat_Unique.Cardinality(False) == 2);
        REQUIRE(stat_Unique.Cardinality(Unknown) == 4);
    }

    SECTION("Cardinality general") {
        Trit_set test_stat_gen(5);
        test_stat_gen[0] = True;
        test_stat_gen[1] = False;
        test_stat_gen[2] = False;
        test_stat_gen[6] = True;
        std::unordered_map<Trit , int> stat = test_stat_gen.Cardinality();
        REQUIRE(stat[True] == 2);
        REQUIRE(stat[False] == 2);
        REQUIRE(stat[Unknown] == 3);
    }

    SECTION("Trim") {
        Trit_set set(10);
        set.Trim(5);
        REQUIRE(set.Size() == 5);
        REQUIRE(set.Capacity() == 3);
    }

    SECTION("Logical length") {
        Trit_set set(10);
        REQUIRE(set.Logical_length() == 0);

        set[2] = True;
        REQUIRE(set.Logical_length() == 3);

        set[5] = False;
        REQUIRE(set.Logical_length() == 6);

        set[12] = True;
        REQUIRE(set.Logical_length() == 13);
    }
}

#endif