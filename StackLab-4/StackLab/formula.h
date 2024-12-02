/////////////////CONVERSION FROM INFIX FORM TO POSTFIX FORM
////
////
////
////


#pragma once
#include "stack.h"
#include <iostream>

const size_t _maxLength = 255;





class TFormula : public TStack
{
private:
	std::string _formula[_maxLength];					//inputed string
	std::string _postfixForm[_maxLength];				//postfix form

public:
	TFormula()											//default
	{
		
	}

	int Checker();										//checking for the correct location of the brackets
	int Converter();									//convert to postfix form
	double Calculate();									
};