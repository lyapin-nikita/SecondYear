#include <iostream>
#include "Monom.h"
#include "Polynom.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian"); // Для вывода русских комментариев

    cout << "=== ТЕСТИРОВАНИЕ КЛАССА Polynom ===" << endl << endl;

    // 1. Тестирование создания полиномов
    cout << "1. Создание полиномов:" << endl;

    Polynom p1;
    int powers1[] = { 2, 3 };
    p1.AppendMonom(3.5, 2, powers1); // 3.5*x1^2*x2^3

    int powers2[] = { 1, 1 };
    p1.AppendMonom(-2.0, 2, powers2); // -2.0*x1^1*x2^1

    cout << "Полином p1: ";
    p1.Print();

    Polynom p2;
    int powers3[] = { 1, 0 };
    p2.AppendMonom(4.0, 2, powers3); // 4.0*x1^1

    int powers4[] = { 0, 2 };
    p2.AppendMonom(1.5, 2, powers4); // 1.5*x2^2

    cout << "Полином p2: ";
    p2.Print();
    cout << endl;

    // 2. Тестирование сложения полиномов
    cout << "2. Сложение полиномов (p1 + p2):" << endl;
    Polynom sum = p1 + p2;
    sum.Print();
    cout << endl;

    // 3. Тестирование вычитания полиномов
    cout << "3. Вычитание полиномов (p1 - p2):" << endl;
    Polynom diff = p1 - p2;
    diff.Print();
    cout << endl;

    // 4. Тестирование умножения полиномов
    cout << "4. Умножение полиномов (p1 * p2):" << endl;
    Polynom prod = p1 * p2;
    prod.Print();
    cout << endl;

    // 5. Тестирование умножения на скаляр
    cout << "5. Умножение полинома на скаляр (p1 * 2.5):" << endl;
    Polynom scaled = p1 * 2.5;
    scaled.Print();
    cout << endl;

    // 6. Тестирование деления полиномов
    cout << "6. Деление полиномов:" << endl;

    // Создаем полиномы для деления
    Polynom dividend;
    int powers5[] = { 3, 2 };
    dividend.AppendMonom(6.0, 2, powers5); // 6*x1^3*x2^2

    int powers6[] = { 1, 2 };
    dividend.AppendMonom(4.0, 2, powers6); // 4*x1^1*x2^2

    int powers7[] = { 2, 0 };
    dividend.AppendMonom(2.0, 2, powers7); // 2*x1^2

    Polynom divisor;
    int powers8[] = { 2, 1 };
    divisor.AppendMonom(3.0, 2, powers8); // 3*x1^2*x2^1

    int powers9[] = { 1, 1 };
    divisor.AppendMonom(1.0, 2, powers9); // 1*x1^1*x2^1

    cout << "Делимое: ";
    dividend.Print();
    cout << "Делитель: ";
    divisor.Print();

    try {
        std::tuple<Polynom, Polynom> division_result = p1 / p2;
        Polynom quotient = std::get<0>(division_result);
        Polynom remainder = std::get<1>(division_result);
        cout << "Частное: ";
        quotient.Print();
        cout << "Остаток: ";
        remainder.Print();

        // Проверка: dividend = divisor * quotient + remainder
        cout << "Проверка: divisor * quotient + remainder = ";
        (divisor * quotient + remainder).Print();
    }
    catch (const exception& e) {
        cout << "Ошибка деления: " << e.what() << endl;
    }

    cout << endl << "Тестирование завершено." << endl;
    return 0;
}