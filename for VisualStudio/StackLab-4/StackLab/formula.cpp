#include "formula.h"
#include <vector>
#include <string>
#include <sstream>
//#include <cstring>
#include <math.h>


int TFormula::CalculatePriority(char c)
{
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == ')') return 1;
	if (c == '(') return 0;
	return -1;
}

int TFormula::CalculatePriority2(std::string str)
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
	std::string input;
	std::cout << "Enter formula: ";
	std::getline(std::cin, input); // Считываем всю строку
	_formula_str = input;

	std::string currentToken;
	for (char c : input) {
		if (isdigit(c)) {
			currentToken += c; // Накапливаем цифры
		}
		else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') {
			if (!currentToken.empty()) {
				_formula2.push_back(currentToken); // Добавляем число, если есть
				currentToken.clear();
			}
			_formula2.push_back(std::string(1, c)); // Добавляем оператор или скобку
		}
		else if (c == ' ') {
			if (!currentToken.empty()) {
				_formula2.push_back(currentToken); // Добавляем число, если есть
				currentToken.clear();
			}
		}
	}
	if (!currentToken.empty()) {
		_formula2.push_back(currentToken); // Добавляем последнее число, если есть
	}
}

void TFormula::OutputInputStr2()
{
	for (size_t i = 0; i < _formula2.size(); i++)
	{
		std::cout << '<' << _formula2[i] << '>';
	}
	std::cout << "\n";
}


void TFormula::OutputPostFix()
{
	std::cout << _postfixForm;
}


void TFormula::OutputPostFix2() {
	std::cout << "Postfix form: ";
	for (const auto& token : _postfixForm2) {
		std::cout << token << " ";
	}
	std::cout << std::endl;
}

/// <summary>
/// ������ ������� ��������� ����� ����������� ������������� ������ � ������� ������
/// </summary>
/// <returns>���������� �������� ������������� ������</returns>
int TFormula::Checker()
{
	int res = 0;
	int index = 0;
	std::vector<int> firstColum; // (
	std::vector<int> secondColum; // )
	TStack<int> s;

	
	for (size_t i = 0; i < _formula_str.size();i++)
	{
		if (_formula_str[i] == '(')
		{
			index++;
			s.put(index);
		}
		else if (_formula_str[i] == ')')
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
		while (!s.isEmpty())
		{
			firstColum.push_back(s.get());
			secondColum.push_back(0);
		}
	}

	std::cout << "Output table:" << '\n';
	for (size_t i = 0; i < firstColum.size(); i++)
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
	TStack<std::string> stack;
	_postfixForm2.clear(); // Очищаем вектор перед заполнением

	for (size_t i = 0; i < _formula2.size(); i++) {
		if (_formula2[i].empty()) continue; // Пропускаем пустые строки

		int pr = CalculatePriority2(_formula2[i]);

		if (pr == -1) {
			_postfixForm2.push_back(_formula2[i]);
		}
		else if (pr == 0) {
			if (_formula2[i] == "(") {
				stack.put(_formula2[i]);
			}
			else if (_formula2[i] == ")") {
				while (!stack.isEmpty() && stack.peek() != "(") {
					_postfixForm2.push_back(stack.get());
				}
				if (!stack.isEmpty()) {
					stack.get(); // Удаляем '(' из стека, не добавляя в постфиксную форму
				}
				else {
					throw std::runtime_error("Mismatched parentheses");
				}
			}
		}
		else { // Операторы
			while (!stack.isEmpty() && CalculatePriority2(stack.peek()) >= pr) {
				_postfixForm2.push_back(stack.get());
			}
			stack.put(_formula2[i]);
		}
	}

	while (!stack.isEmpty()) {
		if (stack.peek() == "(" || stack.peek() == ")") {
			/*throw std::runtime_error("Mismatched parentheses")*/;
			stack.get();
		}
		_postfixForm2.push_back(stack.get());
	}
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



