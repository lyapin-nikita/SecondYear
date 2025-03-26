#pragma once
#include <cstddef>
#include <iostream>

using namespace std;

class Monom{
private:
    double _coeff;
    size_t _size;
    int* _powers;
public:
    Monom(double coeff, size_t size, int* powers);
    double GetCoeff() const;
    string Print() const;

    Monom(const Monom& mon);
    bool operator==(const Monom& m) const;
    Monom& operator=(const Monom& mon);
    Monom operator+(const Monom& mon)const;
    bool IsPowersEquel(const Monom& mon) const;
    Monom operator-(const Monom& mon)const;
    Monom operator*(const Monom& mon) const;
    Monom operator*(int number) const;
    Monom operator/(const Monom& mon) const;
    ~Monom();

    bool CanDiv(const Monom &mon) const;

    int GetDegree() const;

    size_t GetSize() const;

    int *GetPowers() const;
};