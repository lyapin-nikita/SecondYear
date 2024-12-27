/////////////////CONVERSION FROM INFIX FORM TO POSTFIX FORM
////
////
////
////



// TODO: дописать вывод строк, вычисление значения





#pragma once
#include "stack.h"
#include <iostream>


const size_t _maxLength = 255;





class TFormula
{
private:
	char _formula[_maxLength];					//inputed string
	char _postfixForm[_maxLength];				//postfix form

	int CalculatePriority(char c);

public:
	TFormula()											//default
	{
		Input();
		if (Checker() == 0) 
		{ 
			Converter(); 
		}
		else
		{
			std::cout << "Incorrect Brackets!";
		}
	}

	void Input();
	void OutputInputStr();
	void OutputPostFix();
	int Checker();										//checking for the correct location of the brackets
	void Converter();									//convert to postfix form
	double Calculate();									
};



