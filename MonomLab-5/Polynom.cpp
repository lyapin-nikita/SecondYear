#include "Polynom.h"
#include <iostream>
#include <string>
using namespace std;

Polynom::Polynom() {
    _head = nullptr;
}

Polynom::Polynom(const Polynom &tmp) {
    _head = nullptr; // Создаём новый список
    Node* current = tmp._head;
    while (current != nullptr) {
        AppendMonom(current->GetMonom());
        current = current->Next;
    }
}

void Polynom::AppendMonom(Monom monom) {
    if (monom.GetCoeff() == 0) return; // Не добавляем нулевые мономы

    if (_head == nullptr) {
        _head = new Node(monom);
        return;
    }

    Node* node = _head;
    Node* prev = nullptr;

    while (node) {
        if (node->GetMonom().IsPowersEquel(monom)) {
            Monom result = node->GetMonom() + monom;
            if (!result.GetCoeff()) {
                DeleteMonom(node);
                return;
            }
            node->Update(result);
            return;
        }
        prev = node;
        node = node->Next;
    }

    prev->Next = new Node(monom);
}

void Polynom::AppendMonom(double coef, size_t size, int *powers) {
    Monom monom(coef, size, powers);
    AppendMonom(monom);
}

void Polynom::DeleteMonom(Node *monom) {
    if (!_head || !monom) return;

    if (_head == monom){
        Node* temp = _head;
        _head = _head->Next;
        delete temp;
        return;
    }

    Node* prev = _head;
    Node* temp = _head->Next;

    while (temp) {
        if (temp == monom) {
            prev->Next = temp->Next;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->Next;
    }
}

void Polynom::Print() {
    Node* tmp = _head;
    string res = "";
    while (tmp != nullptr) {
        if (tmp == _head){
            res += tmp->GetMonom().Print();
        }
        else {
            if (tmp->GetMonom().GetCoeff() > 0)
                res+= " + ";
            else
                res+= " - ";
            res += tmp->GetMonom().Print();
        }
        tmp = tmp->Next;
    }
    cout << res << endl;
}


Polynom Polynom::operator+(const Polynom &polynom) const {
    Polynom result(*this);
    Node* new_polynom = polynom._head;

    while (new_polynom != nullptr)
    {
        result.AppendMonom(new_polynom->GetMonom());
        new_polynom = new_polynom->Next;
    }
    return result;
}

Polynom Polynom::operator-(const Polynom &polynom) const {
    Polynom result(*this);
    Node* new_polynom = polynom._head;

    while (new_polynom != nullptr)
    {
        result.AppendMonom(new_polynom->GetMonom() * -1 );
        new_polynom = new_polynom->Next;
    }
    return result;
}

Polynom Polynom::operator*(const Polynom &polynom) const {
    Polynom result;

    Node* left_polynom = _head;
    while (left_polynom != nullptr){
        Node* right_polynom = polynom._head;
        while (right_polynom != nullptr){
            result.AppendMonom(left_polynom->GetMonom() * right_polynom->GetMonom());
            right_polynom = right_polynom->Next;
        }
        left_polynom = left_polynom->Next;
    }
    return result;
}


string Polynom::GetLen() {
    int length = 0;
    Node* current = _head;
    while (current != nullptr) {
        length++;
        current = current->Next;
    }
    return to_string(length);
}


Monom Polynom::FindGreatMonom() const {
    if (_head == nullptr) {
        throw std::runtime_error("Empty polynomial");
    }

    Node* current = _head;
    Monom greatMonom = current->GetMonom();

    while (current != nullptr) {
        if (current->GetMonom().GetDegree() > greatMonom.GetDegree()) {
            greatMonom = current->GetMonom();
        }
        current = current->Next;
    }

    return greatMonom;
}

Polynom Polynom::operator*(double scalar) const {
    Polynom result;

    Node* current = _head;
    while (current != nullptr) {
        Monom monom = current->GetMonom();
        result.AppendMonom(monom.GetCoeff() * scalar, monom.GetSize(), monom.GetPowers());
        current = current->Next;
    }

    return result;
}

std::tuple<Polynom, Polynom> Polynom::operator/(const Polynom& divisor) const {
    if (divisor._head == nullptr) {
        throw std::runtime_error("Division by zero polynomial");
    }

    Polynom dividend(*this);
    Polynom quotient;
    Polynom remainder;

    Monom divisorGreat = divisor.FindGreatMonom();

    while (dividend._head != nullptr) {
        Monom dividendGreat = dividend.FindGreatMonom();

        if (!dividendGreat.CanDiv(divisorGreat)) {
            remainder.AppendMonom(dividendGreat);
            dividend.DeleteMonom(dividend._head);
            continue;
        }

        Monom currentQuotient = dividendGreat / divisorGreat;
        quotient.AppendMonom(currentQuotient);

        Polynom tempPoly;
        tempPoly.AppendMonom(currentQuotient);
        Polynom toSubtract = divisor * tempPoly;
        dividend = dividend - toSubtract; // Исправлено: вычитаем, а не добавляем
    }

    return std::make_tuple(quotient, remainder);
}





