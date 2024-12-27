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

std::ostream& operator<<(std::ostream& os, const BitField& bf) {
    for (size_t i = 0; i < bf.GetLength(); ++i) {
        os << static_cast<int>(bf.GetBit(i));
    }
    return os;
}



std::string MorseCode(char c) {
    c = std::toupper(c); // Преобразуем в верхний регистр для упрощения
    switch (c) {
        case 'A': return ".-0";
        case 'B': return "-...0";
        case 'C': return "-.-.0";
        case 'D': return "-..0";
        case 'E': return ".0";
        case 'F': return "..-.0";
        case 'G': return "--.0";
        case 'H': return "....0";
        case 'I': return "..0";
        case 'J': return ".---0";
        case 'K': return "-.-0";
        case 'L': return ".-..0";
        case 'M': return "--0";
        case 'N': return "-.0";
        case 'O': return "---0";
        case 'P': return ".--.0";
        case 'Q': return "--.-0";
        case 'R': return ".-.0";
        case 'S': return "...0";
        case 'T': return "-0";
        case 'U': return "..-0";
        case 'V': return "...-0";
        case 'W': return ".--0";
        case 'X': return "-..-0";
        case 'Y': return "-.--0";
        case 'Z': return "--..0";
        case '1': return ".----0";
        case '2': return "..---0";
        case '3': return "...--0";
        case '4': return "....-0";
        case '5': return ".....0";
        case '6': return "-....0";
        case '7': return "--...0";
        case '8': return "---..0";
        case '9': return "----.0";
        case '0': return "-----0";
        case ' ': return "";
        default: return ""; // Символ не найден
    }
}

void EncodeToBitField(const std::string& text, BitField& bf) {
    std::string morseCode;
    for (char c : text) {
        morseCode += MorseCode(c);
    }

    if (morseCode.length() > bf.GetLength()) {
        throw std::runtime_error("BitField is too small");
    }

    int j = 0;
    int k = 0;
    for (int i = 0; i < bf.GetLength(); i++)
    {
        if (morseCode[i] == '0') { bf._masForMorse.push_back(j); j = 0; k++; continue; }
        else if (morseCode[i] == '-') bf.SetBit(i-k);
        j++;
    }
}

char DecodeMorseChar(const std::string& morseCode) {
    if (morseCode == ".-") return 'A';
    if (morseCode == "-...") return 'B';
    if (morseCode == "-.-.") return 'C';
    if (morseCode == "-..") return 'D';
    if (morseCode == ".") return 'E';
    if (morseCode == "..-.") return 'F';
    if (morseCode == "--.") return 'G';
    if (morseCode == "....") return 'H';
    if (morseCode == "..") return 'I';
    if (morseCode == ".---") return 'J';
    if (morseCode == "-.-") return 'K';
    if (morseCode == ".-..") return 'L';
    if (morseCode == "--") return 'M';
    if (morseCode == "-.") return 'N';
    if (morseCode == "---") return 'O';
    if (morseCode == ".--.") return 'P';
    if (morseCode == "--.-") return 'Q';
    if (morseCode == ".-.") return 'R';
    if (morseCode == "...") return 'S';
    if (morseCode == "-") return 'T';
    if (morseCode == "..-") return 'U';
    if (morseCode == "...-") return 'V';
    if (morseCode == ".--") return 'W';
    if (morseCode == "-..-") return 'X';
    if (morseCode == "-.--") return 'Y';
    if (morseCode == "--..") return 'Z';
    if (morseCode == ".----") return '1';
    if (morseCode == "..---") return '2';
    if (morseCode == "...--") return '3';
    if (morseCode == "....-") return '4';
    if (morseCode == ".....") return '5';
    if (morseCode == "-....") return '6';
    if (morseCode == "--...") return '7';
    if (morseCode == "---..") return '8';
    if (morseCode == "----.") return '9';
    if (morseCode == "-----") return '0';
    if (morseCode == "/") return ' ';
    return '\0'; // Возвращаем null-символ, если код не найден
}



std::string DecodeFromBitField(const BitField& bf)
{
     std::string res;
    std::string tmp;
    std::string tmp2;
    
    for (size_t i = 0; i < bf.GetLength(); i++)
    {
        if (bf.GetBit(i)) tmp += '-';
        else tmp += '.';
    }

    size_t j = 1;
    size_t k = 0;
    for (size_t i = 0; i < tmp.length(); i++)
    {
        tmp2 += tmp[i];
        if (k < bf._masForMorse.size() && j == bf._masForMorse[k])
        {
            k++;
            res += DecodeMorseChar(tmp2);
            tmp2.clear();
            j = 1; // Сбрасываем j
        }   
        else
        {
            j++;
        }
    }
    // Обработка оставшегося tmp2
    if (!tmp2.empty()) {
        res += DecodeMorseChar(tmp2);
    }

    return res;
}







    
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
