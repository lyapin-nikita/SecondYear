// template upper triangular matrix + template vector
//by Lyapin Nikita, NNGU @2023




//#ifndef __TMATRIX_H__
//#define __TMATRIX_H__
#pragma once





#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE= 10000;




///////////.....................
// TEMPLATE CLASS "VECTOR" BASED ON WHICH WE'LL BUILD MATRIX
// 
// 
// 
// 
// 
// 
// 
// vector template
template <class Type>
class TVector
{


protected:
  Type *_mem;
  size_t _sz;       // size of vector
  size_t _strtIndx; // index of first vector's elem


public:
  TVector(size_t sz = 10, size_t si = 0);
  TVector(const TVector &v);                // copy constructor
  TVector(TVector&& v);                     // replace constructor
  ~TVector();                               // destructor
  size_t GetSize()      { return _sz; } 
  size_t GetStartIndex(){ return _strtIndx; }
  Type& operator[](size_t pos);             
  bool operator==(const TVector &v) const;  
  bool operator!=(const TVector &v) const;  
  TVector& operator=(const TVector &v);     

  // scalar operations
  TVector  operator+(const Type &val) const;   
  TVector  operator-(const Type &val) const;   
  TVector  operator*(const Type &val) const;   

  // vector operations
  TVector  operator+(TVector &v) const;     
  TVector  operator-(TVector &v) const;     
  Type  operator*(const TVector &v) const;     

  // in-out
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v._mem[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v._mem[i] << ' ';
    return out;
  }
};

template <class Type>
TVector<Type>::TVector(size_t sz, size_t si)
{
    if (sz < 0 ||  si < 0)
        throw std::out_of_range("ERROR_NEGATIVE_NUMBER_IN_CONSTRUCTOR");
    if (sz > MAX_VECTOR_SIZE)
        throw std::out_of_range("ERROR_OUT_OF_RANGE_IN_CONSTRUCTOR");
  
    Type buf = Type();
    _sz = sz;
    _strtIndx = si;
    _mem = new Type[_sz];
    for (int i = 0; i < _sz; ++i)
        _mem[i] = buf;
} /*-------------------------------------------------------------------------*/

template <class Type> //конструктор копирования
TVector<Type>::TVector(const TVector<Type> &v)
{
    _sz = v._sz;
    _strtIndx = v._strtIndx;
    _mem = new Type[_sz];
    for (int i = 0; i < _sz; ++i)
        _mem[i] = v._mem[i];
} /*-------------------------------------------------------------------------*/

template <class Type>
TVector<Type>::~TVector()
{
    delete[] _mem;
} /*-------------------------------------------------------------------------*/




/////GENERAL OPERATIONS


template <class Type> 
Type& TVector<Type>::operator[](size_t pos)
{
    Type zero = Type();

    if (pos < 0)
        throw std::out_of_range("ERROR_SET_ELEMENT_WITH_NEGATIVE_INDEX");
    if (pos >= _sz)
        throw std::out_of_range("ERROR_SET_ELEMENT_WITH_TOO_LARGE_INDEX");
    if (pos < _strtIndx)
        return zero;

    return _mem[pos - _strtIndx];
} /*-------------------------------------------------------------------------*/

template <class Type> 
bool TVector<Type>::operator==(const TVector &v) const
{
    if (_sz != v._sz || _strtIndx != v._strtIndx)
        return false;

    for (size_t i = 0; i < _sz; i++) {
        if (_mem[i] != v._mem[i])
            return false;
    }

    return true;
} /*-------------------------------------------------------------------------*/

template <class Type> 
bool TVector<Type>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class Type> 
TVector<Type>& TVector<Type>::operator=(const TVector &v)
{
    if (this == &v)
        return *this;

    _strtIndx = v._strtIndx;
    if (_sz != v._sz){
        _sz = v._sz;
        delete []_mem;
        _mem = new Type[_sz];
    }

    for (size_t i = 0; i < _sz; i++)
        _mem[i] = v._mem[i];

    return *this;
} /*-------------------------------------------------------------------------*/





///////SCALAR


template <class Type> 
TVector<Type> TVector<Type>::operator+(const Type &val) const
{
    TVector<Type> tmp(_sz + _strtIndx);

    for (size_t i = 0; i < tmp._sz + _strtIndx; i++)
        tmp._mem[i] = _mem[i] + val;
    return tmp;

} /*-------------------------------------------------------------------------*/

template <class Type> 
TVector<Type> TVector<Type>::operator-(const Type &val) const
{
    TVector<Type> tmp(_sz + _strtIndx, 0);

    for (int i = 0; i < tmp._sz + _strtIndx; i++)
        tmp._mem[i] = _mem[i] - val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class Type> 
TVector<Type> TVector<Type>::operator*(const Type &val) const
{
    TVector<Type> tmp = *this;

    for (int i = 0; i < tmp._sz; i++)
        tmp._mem[i] *= val; 
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class Type> 
TVector<Type> TVector<Type>::operator+(TVector<Type> &v) const
{
    if (_strtIndx != v._strtIndx || _sz != v._sz)
        throw "ERROR_NOT_EQUAL_VECTORS";
    
    TVector<Type> tmp(*this);

    for (int i = 0; i < _sz; ++i)
        tmp._mem[i] += v._mem[i];

    return tmp;
} /*-------------------------------------------------------------------------*/

template <class Type> 
TVector<Type> TVector<Type>::operator-(TVector<Type> &v) const
{
    if (_strtIndx != v._strtIndx || _sz != v._sz)
        throw "ERROR_NOT_EQUAL_VECTORS";

    TVector<Type> tmp(*this);

    for (int i = 0; i < _sz; ++i)
        tmp._mem[i] -= v._mem[i];

    return tmp;
} /*-------------------------------------------------------------------------*/

template <class Type> // scalar multiply
Type TVector<Type>::operator*(const TVector<Type> &v) const
{
    if (_strtIndx != v._strtIndx || _sz != v._sz)
        throw "ERROR_NOT_EQUAL_VECTORS";
    
    Type scal = Type();
    
    for (int i = 0; i < _sz; ++i)
        scal += _mem[i] * v._mem[i];
   
    return scal;
} /*-------------------------------------------------------------------------*/















//////////////////////.................
//NEXT WE GONNA BUILD THE CLASS "UPPER TRIANGULAR MATRIX" 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// upper triangular matrix (vector's child)
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           // default
  TMatrix(const TMatrix &mt);                    // copy
  TMatrix(const TVector<TVector<ValType> > &mt); // converter
  bool operator==(const TMatrix &mt) const;      
  bool operator!=(const TMatrix &mt) const;      
  TMatrix& operator= (const TMatrix &mt);        
  TMatrix  operator+ (const TMatrix &mt);        
  TMatrix  operator- (const TMatrix &mt);        

  // in-out
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};




// constructors
template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType>>(s)
{
    if (s > MAX_MATRIX_SIZE || s < 0)
        throw std::out_of_range("ERROR_MATRIX_OUT_OF_RANGE_IN_CONSTRUCTOR");
    for (int i = 0; i < Size; ++i){
        TVector<ValType> buf(Size - i, i);
        pVector[i] = buf;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // copy
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType>>(mt)
{
}

template <class ValType> // converter
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):TVector<TVector<ValType>>(mt) 
{
}

template <class ValType> //
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (Size != mt.Size)
        return false;
    for (int i = 0; i < Size; ++i) {
        if (pVector[i] != mt.pVector[i])
            return false;
    }
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // 
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(mt == *this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // 
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this == &mt)
        return *this;

    if (Size != mt.Size) {
        Size = mt.Size;
        delete[] pVector;
        pVector = new TVector<ValType>[Size];
    }
    for (int i = 0; i < Size; ++i)
        pVector[i] = mt.pVector[i];
    
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw "ERROR_ADD_MATRIX_NOT_EQUAL_SIZE";
   
    TMatrix<ValType> tmp(*this);

    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] = pVector[i] + mt.pVector[i];

    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw "ERROR_SUBSTRACT_MATRIX_NOT_EQUAL_SIZE";

    TMatrix<ValType> tmp(*this);
 
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] = pVector[i] - mt.pVector[i];

    return tmp;
} /*-------------------------------------------------------------------------*/


// #endif
