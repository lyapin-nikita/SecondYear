#include "formula.h"
#include <vector>
#include <string>


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
	TStack<double> stack;
	std::string currentNumber;
	for (int i = 0; _postfixForm[i] != '\0'; ++i) {
		if (isdigit(_postfixForm[i]) || _postfixForm[i] == '.') {
			currentNumber += _postfixForm[i];
		}
		else if (_postfixForm[i] == ' ') {
			if (!currentNumber.empty()) {
				stack.put(std::stod(currentNumber));
				currentNumber = "";
			}
		}
		else if (_postfixForm[i] == '+' || _postfixForm[i] == '-' || _postfixForm[i] == '*' || _postfixForm[i] == '/' || _postfixForm[i] == '^') {
			if (stack.getDataCount() < 2) {
				throw std::runtime_error("Invalid postfix expression");
			}
			double operand2 = stack.get();
			double operand1 = stack.get();
			double result;
			switch (_postfixForm[i]) {
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0) {
					throw std::runtime_error("Division by zero");
				}
				result = operand1 / operand2;
				break;
			case '^':
				result = std::pow(operand1, operand2);
				break;
			default:
				throw std::runtime_error("Invalid operator");
			}
			stack.put(result);
		}
	}
	if (stack.getDataCount() != 1) {
		throw std::runtime_error("Invalid postfix expression");
	}
	return stack.get();
}



//TPostfix::TPostfix(const string& infx) {
//	if (infx == "")
//		throw std::exception("empty infix");
//	infix = infx;
//	std::string::iterator end_pos = std::remove(infix.begin(), infix.end(), ' ');
//	infix.erase(end_pos, infix.end());
//	priority = { {"*", 3}, {"/", 3},
//		{"+", 2}, {"-", 2},
//		{"(", 1}, {"=", 0} };
//	ToPostfix();
//}
//
//void TPostfix::Parse() {
//	for (char c : infix)
//		lexems.push_back(c);
//}
//
//string TPostfix::GetPostfix()const
//{
//	string tmp = "";
//	for (int i = 0; i < postfix.size(); i++)
//	{
//		tmp += postfix[i];
//	}
//	return tmp;
//}
//
//void TPostfix::PrintInfix()
//{
//	std::cout << infix;
//}
//void TPostfix::PrintPostfix()
//{
//	std::cout << GetPostfix();
//}
//
//bool TPostfix::IsCorrect()const
//{
//	return IsCorrectOperands() && IsCorrectOperator() && !IncorrectSybol();
//}
//
//bool TPostfix::IsOperator(int ind)const
//{
//	if (lexems[ind] == '*' || lexems[ind] == '/' ||
//		lexems[ind] == '+' || lexems[ind] == '-')
//		return true;
//	return false;
//}
//
//
//bool TPostfix::IsCorrectOperands()const
//{
//	int flag = 0;
//	int ind = 0;
//	while (ind < lexems.size() - 1)
//	{
//		if (lexems[ind] == ')' && !IsOperator(ind + 1))
//			return false;
//		if (lexems[ind] == '(' && IsOperator(ind + 1))
//			return false;
//		if (IsOperator(ind) || lexems[ind] == '(' || lexems[ind] == ')')
//			ind++;
//		if (lexems[ind] == '.' && IsOperator(ind + 1))
//			return false;
//		int flag = 0;
//		while (isdigit(lexems[ind]) || lexems[ind] == '.')
//		{
//			ind++;
//			if (ind >= lexems.size())
//				break;
//			if (lexems[ind] == '.')
//			{
//				flag++;
//			}
//			if (isalpha(lexems[ind]))
//				return false;
//		}
//		if (flag > 1)
//			return false;
//		if (ind >= lexems.size())
//			break;
//		while (isalpha(lexems[ind]) && !lexems[ind] != '(' && !lexems[ind] != ')')
//		{
//			if (ind >= lexems.size() - 1)
//				break;
//			if (isdigit(lexems[ind + 1]) || (lexems[ind + 1] == '.'))
//				return false;
//
//			ind++;
//		}
//	}
//	return true;
//}
//
//bool TPostfix::IsCorrectOperator()const
//{
//	TStack<char> brackets;
//	int flag = 0;
//	for (char i : lexems)
//	{
//		switch (i)
//		{
//		case '(':
//		{
//			brackets.push('(');
//			flag++; break;
//		}
//		case ')':
//		{
//			if (flag == 0)
//				return false;
//			if (brackets.isEmpty())
//				return false;
//			brackets.Pop();
//			flag++;
//			break;
//		}
//		case '*': case '/': case '+': case '-': case ',':
//		{
//			if (flag == 0 || flag == lexems.size() - 1)
//				return false;
//			if (IsOperator(flag - 1) || IsOperator(flag + 1) ||
//				lexems[flag - 1] == '.' || lexems[flag + 1] == '.'
//				|| lexems[flag + 1] == ')' || lexems[flag - 1] == '(')
//				return false;
//			flag++;
//			break;
//		}
//		default: { flag++; break; }
//		}
//	}
//	if (!brackets.isEmpty())
//		return false;
//
//	return true;
//}
//
//bool TPostfix::IncorrectSybol()const
//{
//	for (int i = 0; i < lexems.size(); i++)
//		if (!IsOperator(i) && !isdigit(lexems[i]) &&
//			!isalpha(lexems[i]) && lexems[i] != '.' &&
//			lexems[i] != '(' && lexems[i] != ')')
//			return true;
//	return false;
//}
//
//void TPostfix::ToPostfix()
//{
//	Parse();
//	if (!IsCorrect())
//	{
//		throw std::exception("invalid infix");
//	}
//	TStack<string> st2(lexems.size());
//	int i = 0;
//	while (i < lexems.size())
//	{
//		string tmp;
//		switch (lexems[i])
//		{
//		case '(':
//		{
//			tmp = lexems[i];
//			st2.push(tmp);
//			i++;
//			break;
//		}
//		case ')':
//		{
//			while (st2.Top() != "(")
//			{
//				postfix.push_back(st2.Pop());
//			}
//			st2.Pop();
//			i++;
//			break;
//		}
//		case '+': case '-': case '*': case '/':
//		{
//			int flag = 0;
//			tmp = lexems[i];
//			if (!st2.isEmpty())
//				while (flag == 0)
//				{
//					if (priority[st2.Top()] >= priority[tmp])
//					{
//						postfix.push_back(st2.Pop());
//						if (st2.isEmpty())
//							break;
//					}
//					else if (isalpha(lexems[i]) || isdigit(lexems[i]))
//						flag++;
//					else
//						flag++;
//				}
//			st2.push(tmp);
//			i++;
//			break;
//		}
//		default:
//		{
//			string operand = "";
//			int flag = 0;
//			while (isdigit(lexems[i]))
//			{
//				operand += lexems[i];
//				i++;
//				if (i >= lexems.size() - 1)
//					break;
//				if (lexems[i] == '.' || isdigit(lexems[i]))
//				{
//					operand += lexems[i];
//					i++;
//				}
//			}
//			if (operand != "")
//			{
//				postfix.push_back(operand);
//				break;
//			}
//			else
//			{
//				while (isalpha(lexems[i]))
//				{
//					operand += lexems[i];
//					i++;
//					if (i >= lexems.size())
//						break;
//				}
//				postfix.push_back(operand);
//			}
//			break;
//		}
//		}
//	}
//	while (!st2.isEmpty())
//	{
//		postfix.push_back(st2.Pop());
//	}
//}
//
//void TPostfix::setOperands()
//{
//	for (int i = 0; i < postfix.size(); i++)
//	{
//		if (postfix[i] == "*" || postfix[i] == "/"
//			|| postfix[i] == "+" || postfix[i] == "-")
//			continue;
//		if (operands.find(postfix[i]) != operands.end())
//			continue;
//		if (!isdigit(postfix[i][0]))
//		{
//			double b;
//			cout << postfix[i] << " = ";
//			cin >> b;
//			operands.insert({ postfix[i], b });
//			continue;
//		}
//		operands.insert({ postfix[i], stod(postfix[i]) });
//	}
//}
//
//
//double TPostfix::Calculate()
//{
//	setOperands();
//	return Calculate(operands);
//}
//
//double TPostfix::Calculate(map<string, double> oprnds)
//{
//	operands = oprnds;
//	int i = 0;
//	TStack<double> st(postfix.size());
//	while (i < postfix.size())
//	{
//		bool flag = true;
//		if (postfix[i] == "+")
//		{
//			double b = st.Pop(), a = st.Pop();
//			st.push(a + b);
//			i++;
//			flag = false;
//			continue;
//		}
//		if (postfix[i] == "*")
//		{
//			double b = st.Pop(), a = st.Pop();
//			st.push(a * b);
//			i++;
//			flag = false;
//			continue;
//		}
//		if (postfix[i] == "-")
//		{
//			double b = st.Pop(), a = st.Pop();
//			st.push(a - b);
//			i++;
//			flag = false;
//			continue;
//		}
//		if (postfix[i] == "/")
//		{
//			double b = st.Pop(), a = st.Pop();
//			if (b == 0.0) throw std::exception("Division by zero");
//			st.push(a / b);
//			i++;
//			flag = false;
//			continue;
//		}
//		if (flag)
//		{
//			st.push(operands[postfix[i]]);
//			i++;
//		}
//	}
//	return st.Pop();
//}