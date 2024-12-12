/////////////////CONVERSION FROM INFIX FORM TO POSTFIX FORM
////
////
////
////



// TODO: дописать





#pragma once
#include "stack.h"
#include <iostream>


const size_t _maxLength = 255;





class TFormula
{
private:
	char _formula[_maxLength];					//inputed string
	char _postfixForm[_maxLength];				//postfix form

public:
	TFormula()											//default
	{
		Input();
		if (Checker() == 0) Converter();
	}

	void Input();
	int Checker();										//checking for the correct location of the brackets
	void Converter();									//convert to postfix form
	double Calculate();									
};