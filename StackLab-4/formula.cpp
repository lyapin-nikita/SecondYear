#include "formula.h"
#include <vector>
//#include <string>
#include <cstring>
#include <math.h>


int TFormula::CalculatePriority(char c)
{
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == ')') return 1;
	if (c == '(') return 0;
	return -1;
}

int CalculatePriority2(std::string str)
{
	if (str == "*" || str == "/") return 3;
	if (str == "+" || str == "-") return 2;
	if (str == ")") return 1;
	if (str == "(") return 0;
	return -1;
}

void TFormula::Input()
{
	std::cin >> _formula;
}

void TFormula::Input2()
{
	std::string tmp;
	std::string numeric;
	std::cin >> tmp;
	for (char c : tmp)
	{
		if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
		{
			_formula2->push_back(numeric);
			numeric.clear();
			std::string bf(1, c);
			_formula2->push_back(bf); 
		}
		else 
		{
			numeric+=c;
		}

	}
}

void TFormula::OutputInputStr2()
{
	for (size_t i = 0; i < _formula2->size(); i++)
	{
		for (size_t j = 0; j < _formula2[i].size(); j++)
		{std::cout << _formula2[i][j];}
	}
	std::cout << "\n";
}


void TFormula::OutputPostFix()
{
	std::cout << _postfixForm;
}


/// <summary>
/// ������ ������� ��������� ����� ����������� ������������� ������ � ������� ������
/// </summary>
/// <returns>���������� �������� ������������� ������</returns>
int TFormula::Checker()
{
	int res = 0;
	int index = 0;
	std::vector <int> firstColum;// (
	std::vector <int> secondColum;// )
	TStack <int> s;


	for (int i = 0; _formula[i] != '\0'; i++)
	{
		if (_formula[i] == '(')
		{
			index++;
			s.put(index);
		}
		if (_formula[i] == ')')
		{
			index++;
			if (!s.isEmpty())
			{
				firstColum.push_back(s.get());
				secondColum.push_back(index);
			}
			else
			{
				firstColum.push_back(0);
				secondColum.push_back(index);
				res++;
			}

		}
	}

	if (!s.isEmpty())
	{
		res += s.getDataCount();
		for (int i = s.getDataCount() - 1; i >= 0; i--)
		{
			firstColum.push_back(s.get());
			secondColum.push_back(0);
		}
	}


	std::cout << "Output table:" << '\n';
	for (int i = 0; i < firstColum.size(); i++)
	{
		std::cout << firstColum[i] << ' ' << secondColum[i] << "\n";
	}


	return res;
}



/// <summary>
/// ������ ������� ������������ ������ ������ � ��������� ����� � �������� � �����������
/// </summary>
void TFormula::Converter()
{
	TStack<char> stack;
	std::string postfix;

	for (int i = 0; _formula[i] != '\0'; ++i) {
		char c = _formula[i];
		int pr = CalculatePriority(c);

		if (pr == -1) { 
			postfix += c;
		}
		else if (pr == 0) { 
			stack.put(c);
		}
		else if (pr == 1) { 
			while (!stack.isEmpty() && stack.peek() != '(') {
				postfix += stack.get();
			}
			if (stack.isEmpty()) {
				throw std::runtime_error("Mismatched parentheses");
			}
			stack.get(); // ������� '('
		}
		else { // ��������
			while (!stack.isEmpty() && CalculatePriority(stack.peek()) >= pr) {
				postfix += stack.get();
			}
			stack.put(c);
		}
	}

	while (!stack.isEmpty()) {
		if (stack.peek() == '(') {
			throw std::runtime_error("Mismatched parentheses");
		}
		postfix += stack.get();
	}
	//std::cout << postfix << std::endl;
	strcpy(_postfixForm, postfix.c_str());
}



double TFormula::Calculate()
{
	TStack<double> stack;

	for (size_t i = 0; _postfixForm[i] != '\0'; i++)
	{
		if (_postfixForm[i] == '+' || _postfixForm[i] == '-' || _postfixForm[i] == '*' || _postfixForm[i] == '/')
		{
			double op2 = stack.get();
			double op1 = stack.get();

			if (_postfixForm[i] == '+') {stack.put(op1+op2);}
			if (_postfixForm[i] == '-') {stack.put(op1-op2);}
			if (_postfixForm[i] == '*') {stack.put(op1*op2);}
			if (_postfixForm[i] == '/') {stack.put(op1/op2);}
		} 
		else 
		{
			stack.put(_postfixForm[i] - '0');
		}
		
	}

	return stack.get();
}



