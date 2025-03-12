

#include <iostream>
#include <math.h>


template <typename T>
struct Node 
{
    T data;         //Data
    Node* next;     //Next Pointer


    Node(const T& value) : data(value), next(nullptr) {}
};



template <typename T>
class TList 
{
private:
    Node<T>* head;  //start of list
    size_t size;    //size of list

public:
    TList() : head(nullptr), size(0) {}

    ~TList() {
        clear();
    }

    //add
    void push_front(const T& value) 
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    //delete 
    void pop_front() 
    {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    void push_back(const T& value) 
    {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    //get
    T front() const 
    {
        if (head) {
            return head->data;
        }
        throw std::out_of_range("list is empty");
    }

   
    bool empty() const 
    {
        return head == nullptr;
    }

    
    size_t getSize() const 
    {
        return size;
    }

    
    void clear() 
    {
        while (head) {
            pop_front();
        }
    }


    T& operator[](size_t index) 
    {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }


    void erase(size_t index) 
    {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            pop_front();
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr; // Keep track of the previous node

        for (size_t i = 0; i < index; ++i) {
            prev = current;
            current = current->next;
        }


        prev->next = current->next;  

        if (current == tail) {
            tail = prev;  
        }

        delete current;  
        size--;         
    }
    
    
    void print() const 
    {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};












/////РЕАЛИЗАЦИЯ МОНОМА

class TMonom {
private:
    double coefficient; 
    int xPower;         
    int yPower;         
    int zPower;         

public:
    TMonom(double coeff = 0.0, int x = 0, int y = 0, int z = 0)
        : coefficient(coeff), xPower(x), yPower(y), zPower(z) {}

    double getCoefficient() const { return coefficient; }
    int getXPower() const { return xPower; }
    int getYPower() const { return yPower; }
    int getZPower() const { return zPower; }

    void setCoefficient(double coeff) { coefficient = coeff; }
    void setXPower(int x) { xPower = x; }
    void setYPower(int y) { yPower = y; }
    void setZPower(int z) { zPower = z; }

    //operators
    TMonom operator*(const TMonom& other) const 
    {
        return TMonom(
            coefficient * other.coefficient,
            xPower + other.xPower,
            yPower + other.yPower,
            zPower + other.zPower
        );
    }

  
    TMonom operator/(const TMonom& other) const {
        if (other.coefficient == 0) 
        {
            throw std::invalid_argument("div to zero");
        }
        return TMonom(
            coefficient / other.coefficient,
            xPower - other.xPower,
            yPower - other.yPower,
            zPower - other.zPower
        );
    }

    
    TMonom pow(int exponent) const {
        if (exponent < 0) 
        {
            throw std::invalid_argument("exp >= 0");
        }
        return TMonom(
            std::pow(coefficient, exponent),
            xPower * exponent,
            yPower * exponent,
            zPower * exponent
        );
    }

   
    bool operator==(const TMonom& other) const 
    {
        return coefficient == other.coefficient &&
               xPower == other.xPower &&
               yPower == other.yPower &&
               zPower == other.zPower;
    }

    //output
    void print() const 
    {
        std::cout << coefficient;
        if (xPower != 0) std::cout << "x^" << xPower;
        if (yPower != 0) std::cout << "y^" << yPower;
        if (zPower != 0) std::cout << "z^" << zPower;
        std::cout << std::endl;
    }
};







//РЕАЛИЗАЦИЯ ПОЛИНОМА НА ОСНОВЕ МОНОМА И ЛИСТА (TMonom и TList)

class TPolinom {
private:
    TList<TMonom> monoms; // Список мономов

    // Упрощение полинома (сложение одинаковых мономов)
    void simplify() {
        for (size_t i = 0; i < monoms.getSize(); ++i) {
            for (size_t j = i + 1; j < monoms.getSize(); ++j) {
                if (monoms[i] == monoms[j]) {
                    monoms[i].setCoefficient(monoms[i].getCoefficient() + monoms[j].getCoefficient());
                    monoms.erase(j);
                    --j; // Уменьшаем индекс, так как список изменился
                }
            }
        }
    }

public:
    // Добавление монома в полином
    void addMonom(const TMonom& monom) {
        monoms.push_back(monom);
        simplify(); // Упрощаем полином после добавления
    }

    // Сложение полиномов
    TPolinom operator+(const TPolinom& other) const {
        TPolinom result = *this;
        for (size_t i = 0; i < other.monoms.getSize(); ++i) {
            result.addMonom(other.monoms[i]);
        }
        return result;
    }

    // Вычитание полиномов
    TPolinom operator-(const TPolinom& other) const {
        TPolinom result = *this;
        for (size_t i = 0; i < other.monoms.getSize(); ++i) {
            TMonom temp = other.monoms[i];
            temp.setCoefficient(-temp.getCoefficient());
            result.addMonom(temp);
        }
        return result;
    }

    // Умножение полиномов
    TPolinom operator*(const TPolinom& other) const {
        TPolinom result;
        for (size_t i = 0; i < monoms.getSize(); ++i) {
            for (size_t j = 0; j < other.monoms.getSize(); ++j) {
                result.addMonom(monoms[i] * other.monoms[j]);
            }
        }
        return result;
    }

    // Деление полиномов (упрощенное, без остатка)
    TPolinom operator/(const TPolinom& other) const {
        TPolinom result;
        for (size_t i = 0; i < monoms.getSize(); ++i) {
            for (size_t j = 0; j < other.monoms.getSize(); ++j) {
                result.addMonom(monoms[i] / other.monoms[j]);
            }
        }
        return result;
    }

    

    // Возведение полинома в степень
    TPolinom pow(int power) const {
        TPolinom result;
        for (size_t i = 0; i < monoms.getSize(); ++i) {
            result.addMonom(monoms[i].pow(power));
        }
        return result;
    }

    // Вывод полинома
    void print() const {
        for (size_t i = 0; i < monoms.getSize(); ++i) {
            monoms[i].print();
            if (i < monoms.getSize() - 1) {
                std::cout << " + ";
            }
        }
        std::cout << std::endl;
    }
};


