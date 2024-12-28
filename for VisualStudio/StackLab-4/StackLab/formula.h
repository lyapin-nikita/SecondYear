/////////////////CONVERSION FROM INFIX FORM TO POSTFIX FORM
////
////
////
////



// TODO: �������� ����� �����, ���������� ��������





#pragma once
#include "stack.h"
#include <iostream>
#include <vector>


const size_t _maxLength = 255;





class TFormula
{
private:
	char _formula[_maxLength];					//inputed string
	char _postfixForm[_maxLength];
	std::string _formula_str;
	std::vector<std::string> _formula2;
	std::vector<std::string> _postfixForm2;				//postfix form

	int CalculatePriority(char c);
	int CalculatePriority2(std::string str);

public:
	TFormula()											//default
	{
		Input2();
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
	void Input2();
	void OutputInputStr2();
	void OutputPostFix();
	void OutputPostFix2();
	int Checker();										//checking for the correct location of the brackets
	void Converter();									//convert to postfix form
	double Calculate();									
};



