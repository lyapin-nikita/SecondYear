#pragma once
#include <tuple>

#include "Node.h"

class Polynom {
private:
    Node* _head;
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
};