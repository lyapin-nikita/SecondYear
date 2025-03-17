/////// MAIN FUNCTION FOR TESTING
// 
// 
// 
// 

#include "stack.h"
#include "formula.h"
#include <iostream>
using namespace std;



int main() 
{

	try
	{
		TFormula formula(InfixFormInput());
		std::cout << "Postfix form: " << formula.getPostfixForm() << std::endl;
		std::cout << "Result: " << formula.Calculate() << std::endl;
	}
	catch (const std::exception& troubles)
	{
		std::cerr << troubles.what();
	}


    return 0;
}