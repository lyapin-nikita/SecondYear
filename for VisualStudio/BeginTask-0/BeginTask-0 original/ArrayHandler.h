#include <cstddef>


template <typename T>
class ArrayHandler 
{
private:
    size_t _size, _power;
    T* _array;
    T _min, _max;
    
public:
    ArrayHandler(size_t size = 10) 
    {
        if (size < 0) throw "invalid input! (size >= 0)"; 
        _size = size;
        _power = 0;
        _array = new T[_size];
    }

    void AppendElem(T elem) 
    {
        if (_power == _size)
        {
            (_size == 0) ? (_size = 10) : (_size *= 2);
            T* new_array = new T[_size];
            for (size_t i = 0; i < _power; i++) { new_array[i] = _array[i]; }
            delete[] _array;
            _array = new_array;

            if (elem > _max) _max = elem;
            if (elem < _min) _min = elem;
        }
        else if (_power == 0) { _min = elem; _max = elem; }
            
        _array[_power] = elem;
        _power++;

        if (elem > _max) _max = elem;
        if (elem < _min) _min = elem;

    }

    bool IsContains(T elem) 
    {
        for (size_t i = 0; i < _size; i++) 
        { 
            if (_array[i] == elem) { return true; }
        }
        
        return false;
    }

    T GetMax() 
    {
        return _max;
    }

    T GetMin() 
    {
        return _min;
    }

    ~ArrayHandler() 
    {
        delete[] _array;
    }

};


