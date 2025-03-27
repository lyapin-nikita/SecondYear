#include <iostream>
#include "Monom.h"
#include "Polynom.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian"); // ��� ������ ������� ������������

    cout << "=== ������������ ������ Polynom ===" << endl << endl;

    // 1. ������������ �������� ���������
    cout << "1. �������� ���������:" << endl;

    Polynom p1;
    int powers1[] = { 2, 3 };
    p1.AppendMonom(3.5, 2, powers1); // 3.5*x1^2*x2^3

    int powers2[] = { 1, 1 };
    p1.AppendMonom(-2.0, 2, powers2); // -2.0*x1^1*x2^1

    cout << "������� p1: ";
    p1.Print();

    Polynom p2;
    int powers3[] = { 1, 0 };
    p2.AppendMonom(4.0, 2, powers3); // 4.0*x1^1

    int powers4[] = { 0, 2 };
    p2.AppendMonom(1.5, 2, powers4); // 1.5*x2^2

    cout << "������� p2: ";
    p2.Print();
    cout << endl;

    // 2. ������������ �������� ���������
    cout << "2. �������� ��������� (p1 + p2):" << endl;
    Polynom sum = p1 + p2;
    sum.Print();
    cout << endl;

    // 3. ������������ ��������� ���������
    cout << "3. ��������� ��������� (p1 - p2):" << endl;
    Polynom diff = p1 - p2;
    diff.Print();
    cout << endl;

    // 4. ������������ ��������� ���������
    cout << "4. ��������� ��������� (p1 * p2):" << endl;
    Polynom prod = p1 * p2;
    prod.Print();
    cout << endl;

    // 5. ������������ ��������� �� ������
    cout << "5. ��������� �������� �� ������ (p1 * 2.5):" << endl;
    Polynom scaled = p1 * 2.5;
    scaled.Print();
    cout << endl;

    // 6. ������������ ������� ���������
    cout << "6. ������� ���������:" << endl;

    // ������� �������� ��� �������
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

    cout << "�������: ";
    dividend.Print();
    cout << "��������: ";
    divisor.Print();

    try {
        std::tuple<Polynom, Polynom> division_result = p1 / p2;
        Polynom quotient = std::get<0>(division_result);
        Polynom remainder = std::get<1>(division_result);
        cout << "�������: ";
        quotient.Print();
        cout << "�������: ";
        remainder.Print();

        // ��������: dividend = divisor * quotient + remainder
        cout << "��������: divisor * quotient + remainder = ";
        (divisor * quotient + remainder).Print();
    }
    catch (const exception& e) {
        cout << "������ �������: " << e.what() << endl;
    }

    cout << endl << "������������ ���������." << endl;
    return 0;
}