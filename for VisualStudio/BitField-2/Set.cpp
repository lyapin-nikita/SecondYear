#include "Set.h"
#include <conio.h>
#include <algorithm>


//TODO нужно переделать функции ввода, вывода(возможно), сравнения




//METODS AND CONSTRUCTS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//default
Set::Set(size_t mp) : _bitField(mp), _maxPower(mp)
{
}

//copy
Set::Set(const Set& s) : _bitField(s._bitField), _maxPower(s._maxPower)
{
}

//converting
Set::Set(const BitField& bf) : _bitField(bf), _maxPower(bf.GetLength())
{
}

//return maxpower
size_t Set::GetMaxPower(void) const 
{
    return _maxPower;
}



//return bit
int Set::IsMember(const uint64_t Elem) const
{
    if (Elem < 0 || Elem >= _maxPower)
        throw std::out_of_range("Bit index out of range");

    return _bitField.GetBit(Elem);
}

//set bit in bitfield
void Set::InsElem(const uint64_t Elem)
{
    if (Elem < 0 || Elem >= _maxPower)
        throw std::out_of_range("Bit index out of range");
    _bitField.SetBit(Elem);
}

//delete element
void Set::DelElem(const uint64_t Elem)
{
    if (Elem < 0 || Elem >= _maxPower)
        throw std::out_of_range("Bit index out of range");
    _bitField.ClrBit(Elem);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












//OPERATORS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Set::operator BitField()
{
    return _bitField;
}

Set& Set::operator=(const Set& s)
{
    if (this == &s)
        return *this;
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this;
}


int Set::operator==(const Set& s) const
{
    if (_maxPower != s._maxPower)
        return 0;
    if (_bitField != s._bitField)
        return 0;
    return 1;
}

int Set::operator!=(const Set& s) const
{
    return !(*this == s);
}

 Set Set::operator+(const Set& s) 
 {
     Set tmp(std::max(_maxPower, s.GetMaxPower()));
     tmp._bitField = _bitField | s._bitField;
     return tmp;
 }

Set Set::operator+(const uint64_t Elem)
{
    if (Elem < 0 || Elem >= _maxPower)
        throw std::out_of_range("Bit index out on range");
    Set tmp(*this);
    tmp._bitField.SetBit(Elem);
    return tmp;
}

Set Set::operator-(const uint64_t Elem)
{
    if (Elem < 0 || Elem >= _maxPower)
        throw std::out_of_range("Bit index out of range");
    Set tmp(*this);
    tmp._bitField.ClrBit(Elem);
    return tmp;
}

 Set Set::operator*(const Set& s) 
 {
     Set tmp(std::max(_maxPower, s.GetMaxPower()));
     tmp._bitField = _bitField & s._bitField;
     return tmp;
 }

Set Set::operator~(void) 
{
    Set tmp(*this);
    tmp._bitField = ~tmp._bitField;
    return tmp;
}

std::vector<uint64_t> Set::GetPrimary()
{
    std::vector <uint64_t> result;
    result.push_back(1);
    bool isPrime;
    for (int i = 2; i < _maxPower; i++)
    {
                isPrime = true;
                for (int j = 2; j < i - 1; j++) {
                    if (i % j == 0) isPrime = false;
                }
                if (isPrime == true && IsMember(i) == true) result.push_back(i);
    }


    return result;
}

//std::vector<uint64_t> Set::GetPrimary() {
//    bool isPrime;
//    std::vector<uint64_t> prime_numbers;
//    prime_numbers.push_back(1);
//    for (int i = 2; i < _maxPower; i++) {
//        isPrime = true;
//        for (int j = 2; j < i - 1; j++) {
//            if (i % j == 0) isPrime = false;
//        }
//        if (isPrime == true && IsMember(i) == true) prime_numbers.push_back(i);
//    }
//    return prime_numbers;
//}

//std::ostream& operator<<(std::ostream& os, const Set& osc) {
//    for (size_t i = 0; i < _maxPower; ++i) {
//        if (IsMember(i)) {
//            os << i << " ";
//        }
//        if ((i + 1) % 10 == 0) { 
//            os << "\n";
//        }
//    }
//    return os;
//}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Set& osc)
{
        for (size_t i = 2; i < osc._maxPower; ++i) {
            if (osc.IsMember(i)) 
            {
                os << i << " ";
            }
            if ((i + 1) % 10 == 0) 
            { 
                os << "\n";
            }
        }
    return os;
}
