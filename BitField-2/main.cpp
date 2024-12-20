//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "Set.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char **argv) {

    // ::testing::InitGoogleTest(&argc, argv);

    // return RUN_ALL_TESTS();
    
    BitField _morseTest(100);
    EncodeToBitField("Hello World", _morseTest);
    std::cout << _morseTest << std::endl;


    
}