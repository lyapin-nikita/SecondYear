#pragma once
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>
#include "Node.h"

class Polynom {
private:
    Node* _head;





    //for input
    //char minOrPlus(char tmp) { if (tmp == '+' || tmp == '-') return '+'; return '-'; }
public:
    Polynom();
    Polynom(const Polynom& tmp);
    void AppendMonom(Monom monom);
    void AppendMonom(double coef, size_t size, int* powers);
    void DeleteMonom(Node* monom);
    void Print();
    string GetLen();

    Polynom operator+(const Polynom& polynom) const;
    Polynom operator-(const Polynom& polynom) const;
    Polynom operator*(const Polynom& polynom) const;

    Monom Lead() const;

    Monom FindGreatMonom() const;

    Polynom operator*(double scalar) const;

    std::tuple<Polynom, Polynom> operator/(const Polynom &divisor) const;



    //перегрузка ввода
    friend std::istream& operator>>(std::istream& is, Polynom& poly) {
        poly._head = nullptr; // Очищаем предыдущий полином

        std::string input;
        std::getline(is, input); // Считываем всю строку

        // Удаляем все пробелы из строки для упрощения обработки
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

        if (input.empty()) return is;

        // Обрабатываем первый символ, если это не знак
        size_t pos = 0;
        if (input[0] != '+' && input[0] != '-') {
            input.insert(0, "+"); // Добавляем явный плюс для первого монома
        }

        // Разбиваем строку на мономы
        std::vector<std::string> monomStrings;
        size_t start = 0;
        while (start < input.length()) {
            size_t end = input.find_first_of("+-", start + 1);
            if (end == std::string::npos) {
                monomStrings.push_back(input.substr(start));
                break;
            }
            monomStrings.push_back(input.substr(start, end - start));
            start = end;
        }

        // Парсим каждый моном
        for (const auto& monomStr : monomStrings) {
            if (monomStr.empty()) continue;

            // Определяем знак коэффициента
            char sign = monomStr[0];
            double coeff = 1.0;
            if (sign == '-') coeff = -1.0;

            // Парсим коэффициент и переменные
            size_t coeff_end = 1;
            while (coeff_end < monomStr.length() &&
                (isdigit(monomStr[coeff_end]) || monomStr[coeff_end] == '.')) {
                coeff_end++;
            }

            if (coeff_end > 1) {
                // Если есть числовой коэффициент
                std::string coeffStr = monomStr.substr(1, coeff_end - 1);
                coeff *= std::stod(coeffStr);
            }

            // Парсим переменные и их степени
            std::string varsPart = monomStr.substr(coeff_end);
            size_t varCount = 3; // Предполагаем максимум 3 переменные (x1, x2, x3)
            int* powers = new int[varCount] {0}; // Инициализируем нулями

            size_t var_pos = 0;
            while (var_pos < varsPart.length()) {
                if (varsPart[var_pos] == 'x') {
                    var_pos++;
                    if (var_pos >= varsPart.length() || !isdigit(varsPart[var_pos])) {
                        throw std::runtime_error("Invalid variable format");
                    }

                    int var_num = varsPart[var_pos] - '0';
                    if (var_num < 1 || var_num > varCount) {
                        throw std::runtime_error("Variable number out of range");
                    }

                    // Проверяем степень
                    int power = 1;
                    if (var_pos + 1 < varsPart.length() && varsPart[var_pos + 1] == '^') {
                        var_pos += 2;
                        if (var_pos >= varsPart.length() || !isdigit(varsPart[var_pos])) {
                            throw std::runtime_error("Invalid power format");
                        }
                        power = 0;
                        while (var_pos < varsPart.length() && isdigit(varsPart[var_pos])) {
                            power = power * 10 + (varsPart[var_pos] - '0');
                            var_pos++;
                        }
                    }
                    else {
                        var_pos++;
                    }

                    powers[var_num - 1] = power;
                }
                else {
                    var_pos++;
                }
            }

            // Добавляем моном в полином
            poly.AppendMonom(coeff, varCount, powers);
            delete[] powers;
        }

        return is;
    }
};



