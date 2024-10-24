#include "Set.h"
#include <conio.h>
#include <algorithm>
//TODO нужно переделать функции ввода, вывода(возможно), сравнения




//METODS AND CONSTRUCTS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//default
Set::Set(int mp) : bitField(mp), MaxPower(mp)
{
}

//copy
Set::Set(const Set& s) : bitField(s.bitField), MaxPower(s.MaxPower)
{
}

//converting
Set::Set(const BitField& bf) : bitField(bf), MaxPower(bf.GetLength())
{
}

//return maxpower
int Set::GetMaxPower(void) const 
{
    return MaxPower;
}

//return bit
int Set::IsMember(const int Elem) const 
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Method is not implemented";

    return bitField.GetBit(Elem);
}

//set bit in bitfield
void Set::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Method is not implemented";
    bitField.SetBit(Elem);
}

//
void Set::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Method is not implemented";
    bitField.ClrBit(Elem);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












//OPERATORS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Set::operator BitField()
{
    return bitField;
}

const Set& Set::operator=(const Set& s)
{
    if (this == &s)
        return *this;
    MaxPower = s.MaxPower;
    bitField = s.bitField;
    return *this;
}

int Set::operator==(const Set& s) const
{
    if (MaxPower != s.MaxPower)
        return 0;
    if (bitField != s.bitField)
        return 0;
    return 1;
}

int Set::operator!=(const Set& s) const
{
    return !(*this == s);
}

// Set Set::operator+(const Set& s) 
// {
//     Set tmp(max(MaxPower, s.GetMaxPower()));
//     tmp.bitField = bitField | s.bitField;
//     return tmp;
// }

Set Set::operator+(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Method is not implemented";
    Set tmp(*this);
    tmp.bitField.SetBit(Elem);
    return tmp;
}

Set Set::operator-(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Method is not implemented";
    Set tmp(*this);
    tmp.bitField.ClrBit(Elem);
    return tmp;
}

// Set Set::operator*(const Set& s) 
// {
//     Set tmp(max(MaxPower, s.GetMaxPower()));
//     tmp.bitField = bitField & s.bitField;
//     return tmp;
// }

Set Set::operator~(void) 
{
    Set tmp(*this);
    tmp.bitField = ~tmp.bitField;
    return tmp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////















