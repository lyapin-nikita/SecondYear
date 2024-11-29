#include "BitField.h"
#include <stdint.h>

BitField::BitField(size_t len) {

}

BitField::BitField(const BitField& tmp) {

}

BitField& BitField::operator=(const BitField& tmp) {
    return *this;
}
    
size_t BitField::GetLength() const {
    return 0;
}
void BitField::SetBit(size_t n) {

}
void BitField::ClrBit(size_t n) {

}
uint8_t BitField::GetBit(size_t n) const {

}

bool BitField::operator==(const BitField &tmp) const// сравнение
{
    if ((_sizeBit != tmp._sizeBit) || (_memSize != tmp._memSize)) return false;
    for (int i(0); i < _memSize; ++i) if (_mem[i] != tmp._mem[i]) return false;
    return true;
}

bool BitField::operator!=(const BitField &tmp) const // сравнение
{
    return !(*this == tmp);
}