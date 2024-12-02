


#include <iostream>
#include "stack.h"




void TStack::resize()
{
    T* tmp = new T[_memSize *= 2];
    for (size_t i = 0; i <= _top; i++) { tmp[i] = _mem[i]; }
    delete[] _mem;
    _mem = tmp;
}

void TStack::put(const T& elem)
{
   if (this->isFull())  resize();
   
   _top++;
   _mem[_top] = elem;
   _dataCount++;
}


T TStack::get()
{
    if (this->isEmpty()) { throw std::out_of_range("Stack is empty!"); }
    T res = _mem[_top];
    _mem[_top] = 0;
    --_dataCount;
    --_top;
    return res;
}

int TStack::isEmpty()
{
    return _dataCount == 0;
}

int TStack::isFull()
{
    return _dataCount == _memSize;
}

void TStack::showStack()
{
    std::cout << "Max size of stack: " << _memSize << "; Count of elements: " << _dataCount << std::endl;
    if (isEmpty()) std::cout << "Stack is Empty!";
    else {
            size_t i = _dataCount;
            for (size_t i = _dataCount; i > 0; i--) { std::cout << _mem[i-1] << std::endl; }
         }
}

//size_t TStack::getNextIndex(size_t i)
//{
//    return _top++;
//}
    