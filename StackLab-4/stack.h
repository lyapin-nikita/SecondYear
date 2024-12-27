////////............by Lyapin Nikita, NNGU @2024



// This header file contains the implementation of the Stack template data 
// structure for the implementation of the Laboratory work "Calculating Arithmetic expressions".



#pragma once
#include <iostream>


// global 
const size_t _maxMemSize = 10;



template <class T>
class TStack
{

private:
	T* _mem;								//pointer to mem
	size_t _memSize;						//size of mem massive
	size_t _dataCount;						//count of stack's elements
	size_t _top;

	void resize();
	//virtual size_t getNextIndex(size_t i);

public:
	TStack(size_t sz = 10) : _dataCount(0), _memSize(sz), _top(-1), _mem(new T[sz])
	{};										//default
	TStack(const TStack& tmp);				//copy
	~TStack() { delete[] _mem; };			//destructor

	//methods
	void put(const T& elem);
	T get();
	T peek();
	int isEmpty();
	int isFull();

	TStack& operator= (const TStack& tmp);	//overload
	size_t getMemSize() { return _memSize; };
	size_t getDataCount() { return _dataCount; }
	void showStack();						//output stack's elements
	
};



template <class T>
inline void TStack <T>::resize()
{
	T* tmp = new T[_memSize *= 2];
	for (size_t i = 0; i <= _top; i++) { tmp[i] = _mem[i]; }
	delete[] _mem;
	_mem = tmp;
}

template <class T>
void TStack<T>::put(const T& elem)
{
	if (this->isFull())  resize();

	_top++;
	_mem[_top] = elem;
	_dataCount++;
}

template <class T>
T TStack<T>::get()
{
	if (this->isEmpty()) { throw std::out_of_range("Stack is empty!"); }
	T res = _mem[_top];
	--_dataCount;
	--_top;
	return res;
}

template<class T>
inline T TStack<T>::peek()
{
	if (this->isEmpty()) { throw std::out_of_range("Stack is empty!"); }
	return _mem[_top];
}

template <class T>
int TStack<T>::isEmpty()
{
	return _dataCount == 0;
}

template <class T>
int TStack<T>::isFull()
{
	return _dataCount == _memSize;
}

template <class T>
void TStack <T>::showStack()
{
	std::cout << "Max size of stack: " << _memSize << "; Count of elements: " << _dataCount << std::endl;
	if (isEmpty()) std::cout << "Stack is Empty!";
	else {
		size_t i = _dataCount;
		for (size_t i = _dataCount; i > 0; i--) { std::cout << _mem[i - 1] << std::endl; }
	}
}


