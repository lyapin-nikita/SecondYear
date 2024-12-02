////////............by Lyapin Nikita, NNGU @2024



// This header file contains the implementation of the Stack template data 
// structure for the implementation of the Laboratory work "Calculating Arithmetic expressions".



#pragma once


// global 
const size_t _maxMemSize = 10;
typedef int T;								//type for class




class TStack
{

protected:
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
	virtual T get();
	int isEmpty();
	int isFull();

	TStack& operator= (const TStack& tmp);	//overload

	void showStack();						//output stack's elements
	
};







