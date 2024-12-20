//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "Set.h"
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

    // ::testing::InitGoogleTest(&argc, argv);

    // return RUN_ALL_TESTS();
    
    size_t maxPower = 1000; 
    Set morseSet(maxPower);

    try {
        EncodeToSet("Hello World", morseSet);
        std::cout << morseSet._bitField; // вывод битового поля (для отладки)

        // Добавьте код для вывода или дальнейшей работы с morseSet
    }
    catch (const std::runtime_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    return 0;
    
}