#include "BitField.h"
#include <stdint.h>

using namespace std;


BitField::BitField()
{
    _sizeBit = 0;
    _memSize = 0;
    _mem = nullptr;
}

BitField::BitField(size_t len)
{
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) 
{
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) 
{   
    if (_sizeBit != tmp._sizeBit) {
        delete[] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const 
{
    return _sizeBit;
}
void BitField::SetBit(size_t n) 
{
    if (n >= _sizeBit) throw "Bit out of range!";
    _mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n) 
{
    if (n > _sizeBit - 1) throw "Method is not implemented";
    _mem[GetMemIndex(n)] &= ~GetMask(n);
}

uint8_t BitField::GetBit(size_t n) const 
{
    if (n > _sizeBit - 1) throw "Method is not implemented";

    if ((_mem[GetMemIndex(n)] | GetMask(n)) == _mem[GetMemIndex(n)]) return 1;
    else return 0;
}

BitField BitField::operator|(const BitField& tmp)
{
    const size_t minBitLen = min(_sizeBit, tmp._sizeBit);
    BitField result(1);
    if (_sizeBit < tmp._sizeBit) result = tmp;
    else result = *this;

    for (int i = 0; i < minBitLen; ++i)
    {
        if (GetBit(i) || tmp.GetBit(i)) result.SetBit(i);
        else result.ClrBit(i);
    }
    return result;
}

BitField BitField::operator&(const BitField& tmp)
{
    const int minBitLen = min(_sizeBit, tmp._sizeBit);
    const int maxBitLen = max(_sizeBit, tmp._sizeBit);
    BitField result(maxBitLen);
    for (int i = 0; i < minBitLen; ++i)
    {
        if (GetBit(i) && tmp.GetBit(i)) result.SetBit(i);
    }
    return result;
}

BitField BitField::operator^(const BitField& tmp)
{
    return BitField();
}

bool BitField::operator==(const BitField &tmp) const // сравнение
{
    if ((_sizeBit != tmp._sizeBit) || (_memSize != tmp._memSize)) return false;
    for (int i(0); i < _memSize; ++i) if (_mem[i] != tmp._mem[i]) return false;
    return true;
}

bool BitField::operator!=(const BitField &tmp) const // сравнение
{
    return !(*this == tmp);
}

BitField BitField::operator~()
{
    BitField result(_sizeBit);
    for (int i(0); i < _sizeBit; ++i)
    {
        if (!GetBit(i)) result.SetBit(i);
    }
    return result;
}

BitField::~BitField()
{
    delete this->_mem;
}

size_t BitField::GetMemIndex(size_t n) const
{
    if (n >= _sizeBit) throw "Bit out of range!";
    size_t index = n / (8 * sizeof(uint16_t));
    return index;
}

uint16_t BitField::GetMask(size_t n) const
{
    return 1 << (n % 16);
}