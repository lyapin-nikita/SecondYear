#include "formula.h"
#include <vector>
#include <string>

/// <summary>
/// Внутренняя функция, необходимая в функции Calculate для вычисления приоритета элемента
/// </summary>
/// <param name="c">Символ для вычисления приоритета</param>
/// <returns>Приоритет</returns>
int TFormula::CalculatePriority(char c)
{
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == ')') return 1;
	if (c == '(') return 0;
	return -1;
}

void TFormula::Input()
{
	std::cin >> _formula;
}

void TFormula::OutputPostFix()
{
	std::cout << _postfixForm;
}


/// <summary>
/// Данная функция выполняет поиск неправильно расположенных скобок в входной строке
/// </summary>
/// <returns>Количество ошибочно расположенных скобок</returns>
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
/// Данная функция конвертирует входую строку в инфиксной форме в выходную в постфиксной
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
			stack.get(); // Удаляем '('
		}
		else { // Оператор
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
	strcpy_s(_postfixForm, postfix.c_str());
}



double TFormula::Calculate()
{
	return double();
}
