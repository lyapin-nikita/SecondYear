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
#include <cstring> // Для strcpy и strlen
#include <stdexcept> // Для std::runtime_error
#include "stack.h" // Подключаем ваш header файл для TStack

class TFormula {
private:
  char* _infixForm;
  char* _postfixForm;

public:
  TFormula(const char* infixForm) {
    _infixForm = new char[strlen(infixForm) + 1];
    strcpy(_infixForm, infixForm);
    _postfixForm = new char[2 * strlen(infixForm) + 1]; // Выделяем больше места, чем в исходном выражении
    ConvertToPostfix();
  }

  ~TFormula() {
    delete[] _infixForm;
    delete[] _postfixForm;
  }

  bool isValid(const char* expression);
  int precedence(char op);
  void ConvertToPostfix();
  double Calculate();

  const char* getPostfixForm() const { return _postfixForm; } // Добавлено для отладки
};

bool TFormula::isValid(const char* expression) {
  TStack<char> s;
  for (int i = 0; expression[i] != '\0'; ++i) {
    if (expression[i] == '(') {
      s.put(expression[i]);
    } else if (expression[i] == ')') {
      if (s.isEmpty()) {
        return false;
      }
      s.get();
    }
  }
  return s.isEmpty();
}

int TFormula::precedence(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

void TFormula::ConvertToPostfix() {
    if (!isValid(_infixForm)) {
        throw std::runtime_error("Invalid expression: Parentheses mismatch");
    }

    std::string postfix = "";
    TStack<char> stack;
    std::string numberBuffer = ""; // Буфер для хранения цифр многозначного числа

    for (size_t i = 0; _infixForm[i] != '\0'; ++i) {
        if (isdigit(_infixForm[i])) {
            // Накапливаем цифры в буфере
            numberBuffer += _infixForm[i];
        } else {
            // Если встретили не цифру, добавляем число из буфера в postfix (если он не пустой)
            if (!numberBuffer.empty()) {
                postfix += numberBuffer + " "; // Добавляем пробел для разделения чисел
                numberBuffer = "";
            }

            if (_infixForm[i] == ' ') continue; // Пропускаем пробелы

            if (_infixForm[i] == '(') {
                stack.put(_infixForm[i]);
            } else if (_infixForm[i] == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += stack.get();
                }
                if (!stack.isEmpty() && stack.peek() == '(') {
                    stack.get(); // Удаляем открывающую скобку
                } else {
                    throw std::runtime_error("Mismatched parentheses");
                }
            } else if (_infixForm[i] == '+' || _infixForm[i] == '-' || _infixForm[i] == '*' || _infixForm[i] == '/') {
                while (!stack.isEmpty() && precedence(_infixForm[i]) <= precedence(stack.peek())) {
                    postfix += stack.get();
                }
                stack.put(_infixForm[i]);
            } else {
                throw std::runtime_error("Invalid character in expression");
            }
        }
    }

    // Добавляем оставшееся число из буфера в postfix (если он не пустой)
    if (!numberBuffer.empty()) {
        postfix += numberBuffer + " ";
    }


    while (!stack.isEmpty()) {
        if (stack.peek() == '(') {
            throw std::runtime_error("Mismatched parentheses");
        }
        postfix += stack.get();
    }

    // Убираем лишние пробелы в конце
    while (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    strcpy(_postfixForm, postfix.c_str());
}


double TFormula::Calculate() {
    TStack<double> stack;
    std::string numberBuffer = "";

    for (size_t i = 0; _postfixForm[i] != '\0'; ++i) {
        if (isdigit(_postfixForm[i])) {
            numberBuffer += _postfixForm[i];
        } else if (_postfixForm[i] == ' ' && !numberBuffer.empty()) {
            // Преобразуем число из буфера в double и помещаем в стек
            stack.put(std::stod(numberBuffer));
            numberBuffer = ""; // Очищаем буфер
        }
        else if (_postfixForm[i] == '+' || _postfixForm[i] == '-' || _postfixForm[i] == '*' || _postfixForm[i] == '/') {
            if (stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for operator");
            }
            double op2 = stack.get();
            if (stack.isEmpty()) {
                throw std::runtime_error("Not enough operands for operator");
            }

            double op1 = stack.get();

            if (_postfixForm[i] == '+') {
                stack.put(op1 + op2);
            } else if (_postfixForm[i] == '-') {
                stack.put(op1 - op2);
            } else if (_postfixForm[i] == '*') {
                stack.put(op1 * op2);
            } else if (_postfixForm[i] == '/') {
                if (op2 == 0) {
                    throw std::runtime_error("Division by zero");
                }
                stack.put(op1 / op2);
            }
        }
    }

    if (stack.isEmpty()) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.get();
}

