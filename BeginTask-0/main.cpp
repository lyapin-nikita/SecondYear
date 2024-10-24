//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "ArrayHandler.h"
#include <iostream>

int main(int argc, char **argv) 
{
    //::testing::InitGoogleTest(&argc, argv);

   // return RUN_ALL_TESTS();
   ArrayHandler<int> test1;
   test1.AppendElem(10);
   std::cout << test1.GetMax();
   
}