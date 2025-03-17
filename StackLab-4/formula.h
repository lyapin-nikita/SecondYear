/////////////////CONVERSION FROM INFIX FORM TO POSTFIX FORM
////
////
////
////









// #pragma once
// #include "stack.h"
// #include <iostream>
// #include <vector>


// const size_t _maxLength = 255;





// class TFormula
// {
// private:
// 	char _formula[_maxLength];					//inputed string
// 	char _postfixForm[_maxLength];
// 	std::vector<std::string> _formula2[_maxLength];
// 	std::vector<std::string> _postfixForm2[_maxLength];				//postfix form

// 	int CalculatePriority(char c);
// 	int CalculatePriority2(std::string str);

// public:
// 	TFormula()											//default
// 	{
// 		Input2();
// 		// if (Checker() == 0) 
// 		// { 
// 		// 	Converter(); 
// 		// }
// 		// else
// 		// {
// 		// 	std::cout << "Incorrect Brackets!";
// 		// }
// 	}

// 	void Input();
// 	void Input2();
// 	void OutputInputStr2();
// 	void OutputPostFix();
// 	int Checker();										//checking for the correct location of the brackets
// 	void Converter();									//convert to postfix form
// 	double Calculate();									
// };

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring> // Для strcpy и strlen
#include <stdexcept> // Для std::runtime_error
#include "stack.h" // Подключаем ваш header файл для TStack

class TFormula {
private:
    std::string _infixForm;
    std::string _postfixForm;

public:
    TFormula(const std::string& infixForm) : _infixForm(infixForm) {
        if (!checkBrackets()) {
            throw std::exception("Incorrect placement of brackets");
        }
        ConvertToPostfix();
    }

    ~TFormula() {}

    bool checkBrackets() const;
    bool isValid(const std::string& expression);
    int precedence(const std::string& op);
    void ConvertToPostfix();
    double Calculate();

    const std::string& getPostfixForm() const { return _postfixForm; } // Добавлено для отладки
};

bool TFormula::isValid(const std::string& expression) {
    TStack<char> s;
    for (char ch : expression) {
        if (ch == '(') {
            s.put(ch);
        }
        else if (ch == ')') {
            if (s.isEmpty()) {
                return false;
            }
            s.get();
        }
    }
    return s.isEmpty();
}

int TFormula::precedence(const std::string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool TFormula::checkBrackets() const {
    TStack<size_t> stack; // Используем ваш стек для хранения индексов открывающих скобок

    for (size_t i = 0; i < _infixForm.length(); ++i) {
        char ch = _infixForm[i];

        if (ch == '(') {
            // Запоминаем индекс открывающей скобки
            stack.put(i);
        }
        else if (ch == ')') {
            if (stack.isEmpty()) {
                // Если стек пуст, значит, закрывающая скобка без соответствующей открывающей
                std::cerr << "Error: Extra closing bracket at position " << i << std::endl;
                std::cerr << _infixForm << std::endl;
                std::cerr << std::string(i, ' ') << "^" << std::endl;
                return false;
            }
            else {
                // Убираем соответствующую открывающую скобку из стека
                stack.get();
            }
        }
    }

    if (!stack.isEmpty()) {
        // Если в стеке остались открывающие скобки, значит, они не закрыты
        while (!stack.isEmpty()) {
            size_t pos = stack.get();
            std::cerr << "Error: Unmatched opening bracket!" << std::endl;
            std::cerr << _infixForm << std::endl;
            std::cerr << std::string(pos, ' ') << "^" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "No bracket errors found." << std::endl;
    }

    return true;
}

void TFormula::ConvertToPostfix() {
    if (!isValid(_infixForm)) {
        throw std::runtime_error("Invalid expression: Parentheses mismatch");
    }

    std::stringstream postfix;
    TStack<std::string> stack;
    std::string numberBuffer = ""; // Буфер для хранения цифр многозначного числа

    for (size_t i = 0; i < _infixForm.length(); ++i) {
        char ch = _infixForm[i];

        if (isdigit(ch) || ch == '.') {
            // Накапливаем цифры и точки (для десятичных чисел) в буфере
            numberBuffer += ch;
        }
        else if (ch == ' ') {
            // Пропускаем пробелы
            continue;
        }
        else {
            // Если встретили не цифру, добавляем число из буфера в postfix (если он не пустой)
            if (!numberBuffer.empty()) {
                postfix << numberBuffer << " "; // Добавляем пробел для разделения чисел
                numberBuffer = ""; // Очищаем буфер
            }

            if (ch == '(') {
                stack.put(std::string(1, ch));
            }
            else if (ch == ')') {
                while (!stack.isEmpty() && stack.peek() != "(") {
                    postfix << stack.get() << " ";
                }
                if (!stack.isEmpty() && stack.peek() == "(") {
                    stack.get(); // Удаляем открывающую скобку
                }
                else {
                    throw std::runtime_error("Mismatched parentheses");
                }
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                // Обработка унарного минуса
                if (ch == '-' && (i == 0 || _infixForm[i - 1] == '(' || _infixForm[i - 1] == '+' || _infixForm[i - 1] == '-' || _infixForm[i - 1] == '*' || _infixForm[i - 1] == '/')) {
                    // Это унарный минус
                    stack.put("~"); // Используем ~ для обозначения унарного минуса
                }
                else {
                    // Это бинарный оператор
                    std::string op(1, ch);
                    while (!stack.isEmpty() && precedence(op) <= precedence(stack.peek())) {
                        postfix << stack.get() << " ";
                    }
                    stack.put(op);
                }
            }
            else {
                throw std::runtime_error("Invalid character in expression: " + std::string(1, ch));
            }
        }
    }

    // Добавляем оставшееся число из буфера в postfix (если он не пустой)
    if (!numberBuffer.empty()) {
        postfix << numberBuffer << " ";
    }

    // Добавляем оставшиеся операторы из стека в postfix
    while (!stack.isEmpty()) {
        if (stack.peek() == "(") {
            throw std::runtime_error("Mismatched parentheses");
        }
        postfix << stack.get() << " ";
    }

    // Убираем лишние пробелы в конце
    std::string result = postfix.str();
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    _postfixForm = result;
}

double TFormula::Calculate() {
    TStack<double> stack;
    std::string token;
    std::stringstream postfix(_postfixForm);

    while (postfix >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            // Обрабатываем числа, включая отрицательные
            stack.put(std::stod(token));
        }
        else if (token == "~") {
            // Обработка унарного минуса
            if (stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for unary minus");
            }
            double op = stack.get();
            stack.put(-op); // Применяем унарный минус
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Проверяем, что в стеке достаточно операндов
            if (stack.getDataCount() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }

            double op2 = stack.get();
            double op1 = stack.get();

            if (token == "+") {
                stack.put(op1 + op2);
            }
            else if (token == "-") {
                stack.put(op1 - op2);
            }
            else if (token == "*") {
                stack.put(op1 * op2);
            }
            else if (token == "/") {
                if (op2 == 0) {
                    throw std::runtime_error("Division by zero");
                }
                stack.put(op1 / op2);
            }
        }
        else {
            throw std::runtime_error("Invalid token in postfix expression: " + token);
        }
    }

    // В конце в стеке должен остаться ровно один элемент — результат
    if (stack.getDataCount() != 1) {
        throw std::runtime_error("Invalid postfix expression");
    }

    return stack.get();
}














//Логика ввода инфиксной формы записи
std::string InfixFormInput() {
    std::string infix;
    std::string infixResult = "";
    double value = 0; // Для параметров
    std::cout << "Input infix form expression: ";
    std::getline(std::cin, infix);

    for (size_t i = 0; i < infix.length(); ++i)
    {
        char c = infix[i];

        if (std::isalpha(c)) 
        {                                           // Поддержка переменных в любом регистре
            std::cout << c << ": ";
            std::cin >> value;
            infixResult += std::to_string(value);
        }
        else if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')') 
        {
            infixResult += c;
        }
        else if (std::isdigit(c)) 
        {
            infixResult += c;
        }
        else 
        {
            continue;
        }
    }

    std::cout << infixResult << "\n\n";
    return infixResult;
}
