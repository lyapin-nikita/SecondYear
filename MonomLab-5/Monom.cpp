#include "Monom.h"
#include <sstream>
#include <iomanip>


Monom::Monom(double coeff, size_t size, int *powers) {
    _coeff = coeff;
    _size = size;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = powers[i];  // Копируем значения
    }
}

double Monom::GetCoeff() const {
    return _coeff;
}

string Monom::Print() const {
    if (_coeff == 0) return "";
    string res = "";
    std::ostringstream oss;
    oss << std::setprecision(8) << std::noshowpoint << abs(_coeff);
    res +=  oss.str();

    for (size_t i = 0; i < _size; i++) {
        if (_powers[i] != 0) {
            res += "x" + to_string(i + 1) + "^" + to_string(_powers[i]);
            if (i < _size - 1) res += "*";
        }
    }
    return res;
}

Monom::Monom(const Monom &mon) {
    _coeff = mon._coeff;
    _size = mon._size;
    _powers = new int[_size];
    for (int i = 0; i < _size; i++) {
        _powers[i] = mon._powers[i];
    }
}

bool Monom::operator==(const Monom &m) const {
    return _coeff == m._coeff && this->IsPowersEquel(m);
}

Monom & Monom::operator=(const Monom &mon) {
    if (this == &mon){
        return *this;
    }

    delete [] _powers;
    _coeff = mon._coeff;
    _size = mon._size;
    _powers = new int[_size];
    for (int i = 0; i < _size; i++) {
        _powers[i] = mon._powers[i];
    }
    return *this;
}

Monom Monom::operator+(const Monom &mon) const {
    if (!IsPowersEquel(mon)) {
        throw;
    }
    Monom result(*this);
    result._coeff += mon._coeff;
    return result;
}

bool Monom::IsPowersEquel(const Monom &mon) const {
    if (this->_size != mon._size) {
        return false;
    }
    for (int i = 0; i < this->_size; i++) {
        if (this->_powers[i] != mon._powers[i]) {
            return false;
        }
    }
    return true;
}

Monom Monom::operator-(const Monom &mon) const {
    if (!IsPowersEquel(mon)) {
        throw;
    }
    Monom result(*this);
    result._coeff -= mon._coeff;
    return result;
}

Monom Monom::operator*(const Monom &mon) const {
    size_t max_size = max(this->_size, mon._size);
    int *powers = new int[max_size];
    int* max_arr;
    if (max_size == mon._size) {
        max_arr = mon._powers;
    } else {
        max_arr = _powers;
    }
    size_t min_size = min(this->_size, mon._size);
    for (size_t i = 0; i < max_size; i++) {
        powers[i] = i < min_size ? _powers[i] + mon._powers[i] : max_arr[i];
    }
    return Monom(_coeff * mon._coeff, max_size, powers);
}

Monom Monom::operator*(int number) const {
    Monom result(*this);
    result._coeff *= number;
    return result;
}

Monom Monom::operator/(const Monom &mon) const {
    if (mon._coeff == 0) {
        throw runtime_error("Division by zero");
    }

    size_t max_size = max(this->_size, mon._size);
    size_t min_size = min(this->_size, mon._size);
    int *powers = new int[max_size];
    for(size_t i = 0; i < min_size; i++){
        powers[i] = _powers[i] - mon._powers[i];
    }

    if(this->_size > mon._size){
        for(size_t i = min_size; i < this->_size; i++){
            powers[i] -= _powers[i];
        }
    }
    else{
        for(size_t i = min_size; i < mon._size; i++){
            powers[i] -= mon._powers[i];
        }
    }
    return Monom(_coeff / mon._coeff, max_size, powers);
}

Monom::~Monom() {
    delete[] _powers;
}





bool Monom::CanDiv(const Monom &mon) const {
    // Проверка делимости коэффициентов
    if (mon._coeff == 0) {
        throw std::runtime_error("Division by zero");
    }

    // Проверка степеней
    for (size_t i = 0; i < min(this->_size, mon._size); i++) {
        if (this->_powers[i] < mon._powers[i]) {
            return false; // Степень левого монома меньше, чем у правого
        }
    }

    return true;
}


int Monom::GetDegree() const {
    int degree = 0;
    for (size_t i = 0; i < _size; i++) {
        degree += _powers[i];
    }
    return degree;
}

size_t Monom::GetSize() const {
    return _size;
}

// Возвращает массив степеней
int* Monom::GetPowers() const {
    return _powers;
}

