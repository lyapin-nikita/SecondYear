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
	T* mem;			//pointer to mem
	size_t _memSize;						//size of mem massive
	size_t _dataCount;						//count of stack's elements
	int _top;





public:
	TStack(size_t sz = 10)
	 : _memSize(sz), _dataCount(0), _top(0), _mem(new T[sz])
	{};
											//default
	TStack(const TStack& tmp)
	 : _memSize(tmp._memSize), _dataCount(tmp._dataCount), _top(tmp._top), _mem(new T[tmp._memSize])
	{
		for (size_t i = 0; i < tmp._dataCount; i++)
		{
			_mem[i] = tmp._mem[i];
		}
	};		
											//copy
	TStack(TStack && tmp) noexcept
	 : _mem(tmp._mem), _memSize(tmp._memSize), _dataCount(tmp._dataCount), _top(tmp._top)
	{
		for (size_t i = 0; i < tmp._dataCount; i++)
		{
			_mem[i] = tmp._mem[i];
		}

		tmp._mem = nullptr;
        tmp._memSize = 0;
        tmp._dataCount = 0;
        tmp._top = -1;
	}	
											//move
	~TStack() noexcept
	{
		delete[] _mem;
	};						
											//destructor





	//operators
	TStack& operator= (const TStack& tmp)	//copy
	{
		if (this != &tmp) 
		{ 
            T* newMem = new T[tmp._memSize]; 

            for (size_t i = 0; i < tmp._dataCount; i++) 
			{
                newMem[i] = tmp._mem[i];
            }

            delete[] _mem;
            _mem = newMem;
            _memSize = tmp._memSize;
            _dataCount = tmp._dataCount;
            _top = tmp._top;
        }
        return *this;
	};
	TStack& operator= (TStack&& tmp) noexcept
	{
		if (this != &tmp) 
		{
            delete[] _mem;

            _mem = tmp._mem;
            _memSize = tmp._memSize;
            _dataCount = tmp._dataCount;
            _top = tmp._top;

            
            tmp._mem = nullptr;
            tmp._memSize = 0;
            tmp._dataCount = 0;
            tmp._top = -1;
        }
        return *this;
	}	


	//methods
	void resize();				//_memSize *=2
	void put(const T& elem);	//==push
	T get(); 					//==pop
	T peek() const;				//==const pop
	int isEmpty() const noexcept;
	int isFull() const noexcept;

	size_t getMemSize() const noexcept { return _memSize; };
	size_t getDataCount() const noexcept { return _dataCount; }
	void showStack() const;										//output stack's elements
	
};


    template <class T>
    std::ostream& operator<<(std::ostream& os, const TStack<T>& stack) {
        if (stack.isEmpty()) {
            os << "Stack is empty.";
        }
        else {
            for (int i = stack.getDataCount() - 1; i >= 0; --i) {
                os << stack.peek() << " "; // ������� �������� �����
            }
        }
        return os;
    }


template <class T>
void TStack<T>::resize()
{
    size_t newSize = _memSize * 2;

    T* tmp = new T[newSize];
    for (size_t i = 0; i <= _top; ++i) 
	{
        tmp[i] = _mem[i];
    }

    delete[] _mem;
    _mem = tmp;
    _memSize = newSize;
}

template <class T>
void TStack<T>::put(const T& elem)
{
    if (isFull()) 
	{
        resize();
    }

    _mem[++_top] = elem;
    _dataCount++;
}

template <class T>
T TStack<T>::get()
{
    if (isEmpty())
	{
        throw std::out_of_range("stack is empty.");
    }

    T res = _mem[_top--];
    _dataCount--;
    return res;
}

template <class T>
T TStack<T>::peek() const
{
    if (isEmpty()) 
	{
        throw std::out_of_range("stack is empty.");
    }

    return _mem[_top];
}

template <class T>
int TStack<T>::isEmpty() const noexcept
{
    return _dataCount == 0;
}

template <class T>
int TStack<T>::isFull() const noexcept
{
    return _dataCount == _memSize;
}

template <class T>
void TStack<T>::showStack() const
{
    std::cout << "Max size of stack: " << _memSize << 
	"; Count of elements: " << _dataCount << std::endl;
    if (isEmpty()) 
	{
        std::cout << "Stack is empty.";
    }
	 else 
	{
        for (size_t i = _dataCount - 1; i >= 0; --i) 
		{
            std::cout << _mem[i] << std::endl;
        }
    }
}


