#pragma once
#include <iostream>
#include <stdint.h>
#include <map>
#include <algorithm>
#include <vector>


class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;

    std::vector<int> _masForMorse; //массив для работы с азбукой морзе

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const;

public:
    BitField();
    BitField(size_t len);
    BitField(const BitField& tmp);
    BitField& operator=(const BitField& tmp);
    
    
    size_t GetLength() const; 
    void SetBit(size_t n);
    void ClrBit(size_t n); 
    uint8_t GetBit(size_t n) const; 


    BitField operator|(const BitField& tmp); 
    BitField operator&(const BitField& tmp); 
    BitField operator^(const BitField& tmp); 
    bool operator==(const BitField& tmp) const;
    bool operator!=(const BitField& tmp) const;  
    BitField operator~(); 
    

    friend std::ostream& operator<<(std::ostream& os, const BitField& bf);
    friend std::string MorseCode(char c);
    friend void EncodeToBitField(const std::string& text, BitField& bf);
    friend std::string DecodeFromBitField(const BitField& bf);
    friend char DecodeMorseChar(const std::string& morseCode);
    ~BitField(); 
};