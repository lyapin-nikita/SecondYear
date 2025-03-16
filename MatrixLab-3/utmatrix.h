//#pragma once
//#include <iostream>
//#include <stdexcept> // для стандартных исключений
//#include <utility>   // для std::swap
//
//const int MAX_VECTOR_SIZE = 100000000;
//const int MAX_MATRIX_SIZE = 10000;
//
//// Шаблон вектора
//template <class ValType>
//class TVector {
//protected:
//    ValType* pVector;
//    int Size;       // размер вектора
//    int StartIndex; // индекс первого элемента вектора
//
//public:
//    // Конструкторы и деструктор
//    TVector(int s = 5, int si = 0);
//    TVector(const TVector& v);                // конструктор копирования
//    TVector(TVector&& v) noexcept;            // конструктор перемещения
//    ~TVector();
//
//    // Методы доступа
//    int GetSize() const { return Size; }      // размер вектора
//    int GetStartIndex() const { return StartIndex; } // индекс первого элемента
//
//    // Операторы доступа
//    //ValType& operator[](int pos);
//    ValType& operator[](int pos) { return pVector[pos - StartIndex]; }
//    const ValType& operator[](int pos) const { return pVector[pos - StartIndex]; }
//    //const ValType& operator[](int pos) const;
//
//    // Операторы сравнения
//    bool operator==(const TVector& v) const;
//    bool operator!=(const TVector& v) const;
//
//    // Оператор присваивания
//    TVector& operator=(TVector v); // используем идиому copy-and-swap
//
//    // Скалярные операции
//    TVector operator+(const ValType& val) const;
//    TVector operator-(const ValType& val) const;
//    TVector operator*(const ValType& val) const;
//
//    // Векторные операции
//    TVector operator+(const TVector& v) const;
//    TVector operator-(const TVector& v) const;
//    ValType operator*(const TVector& v) const; // скалярное произведение
//
//    // Оператор +=
//    TVector& operator+=(const TVector& v);
//
//    // Ввод-вывод
//    friend std::istream& operator>>(std::istream& in, TVector& v) {
//        for (int i = 0; i < v.Size; i++)
//            in >> v.pVector[i];
//        return in;
//    }
//
//    friend std::ostream& operator<<(std::ostream& out, const TVector& v) {
//        for (int i = 0; i < v.Size; i++)
//            out << v.pVector[i] << ' ';
//        return out;
//    }
//
//    // Обмен данными между двумя векторами
//    friend void swap(TVector& first, TVector& second) noexcept {
//        using std::swap;
//        swap(first.pVector, second.pVector);
//        swap(first.Size, second.Size);
//        swap(first.StartIndex, second.StartIndex);
//    }
//};
//
//// Реализация методов TVector
//
//template <class ValType>
//TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si) {
//    if (s < 0 || si < 0)
//        throw std::invalid_argument("Negative size or start index in TVector constructor");
//    if (s > MAX_VECTOR_SIZE)
//        throw std::out_of_range("Vector size exceeds maximum allowed size");
//
//    pVector = new ValType[Size](); // инициализация нулями
//}
//
//template <class ValType>
//TVector<ValType>::TVector(const TVector& v) : Size(v.Size), StartIndex(v.StartIndex) {
//    pVector = new ValType[Size];
//    for (int i = 0; i < Size; ++i)
//        pVector[i] = v.pVector[i];
//}
//
//template <class ValType>
//TVector<ValType>::TVector(TVector&& v) noexcept
//    : pVector(v.pVector), Size(v.Size), StartIndex(v.StartIndex) {
//    v.pVector = nullptr;
//    v.Size = 0;
//    v.StartIndex = 0;
//}
//
//template <class ValType>
//TVector<ValType>::~TVector() {
//    delete[] pVector;
//}
//
//// template <class ValType>
//// ValType& TVector<ValType>::operator[](int pos) {
////     if (pos < StartIndex || pos >= Size + StartIndex)
////         throw std::out_of_range("Index out of range in TVector::operator[]");
////     return pVector[pos - StartIndex];
//// }
//
//// template <class ValType>
//// const ValType& TVector<ValType>::operator[](int pos) const {
////     if (pos < StartIndex || pos >= Size + StartIndex)
////         throw std::out_of_range("Index out of range in TVector::operator[]");
////     return pVector[pos - StartIndex];
//// }
//
//template <class ValType>
//bool TVector<ValType>::operator==(const TVector& v) const {
//    if (Size != v.Size || StartIndex != v.StartIndex)
//        return false;
//
//    for (int i = 0; i < Size; ++i) {
//        if (pVector[i] != v.pVector[i])
//            return false;
//    }
//    return true;
//}
//
//template <class ValType>
//bool TVector<ValType>::operator!=(const TVector& v) const {
//    return !(*this == v);
//}
//
//template <class ValType>
//TVector<ValType>& TVector<ValType>::operator=(TVector v) {
//    swap(*this, v);
//    return *this;
//}
//
//template <class ValType>
//TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
//    TVector<ValType> tmp(*this);
//    for (int i = 0; i < Size; ++i)
//        tmp.pVector[i] += val;
//    return tmp;
//}
//
//template <class ValType>
//TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
//    TVector<ValType> tmp(*this);
//    for (int i = 0; i < Size; ++i)
//        tmp.pVector[i] -= val;
//    return tmp;
//}
//
//template <class ValType>
//TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
//    TVector<ValType> tmp(*this);
//    for (int i = 0; i < Size; ++i)
//        tmp.pVector[i] *= val;
//    return tmp;
//}
//
//template <class ValType>
//TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
//    if (StartIndex != v.StartIndex || Size != v.Size)
//        throw std::invalid_argument("Vectors have different sizes or start indices");
//
//    TVector<ValType> tmp(*this);
//    for (int i = 0; i < Size; ++i)
//        tmp.pVector[i] += v.pVector[i];
//    return tmp;
//}
//
//template <class ValType>
//TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
//    if (StartIndex != v.StartIndex || Size != v.Size)
//        throw std::invalid_argument("Vectors have different sizes or start indices");
//
//    TVector<ValType> tmp(*this);
//    for (int i = 0; i < Size; ++i)
//        tmp.pVector[i] -= v.pVector[i];
//    return tmp;
//}
//
//template <class ValType>
//ValType TVector<ValType>::operator*(const TVector& v) const {
//    if (StartIndex != v.StartIndex || Size != v.Size)
//        throw std::invalid_argument("Vectors have different sizes or start indices");
//
//    ValType scal = ValType();
//    for (int i = 0; i < Size; ++i)
//        scal += (pVector[i] * v.pVector[i]);
//    return scal;
//}
//
//template <class ValType>
//TVector<ValType>& TVector<ValType>::operator+=(const TVector& v) {
//    if (Size != v.Size || StartIndex != v.StartIndex)
//        throw std::invalid_argument("Vectors must have the same size and start index");
//
//    for (int i = 0; i < Size; ++i) {
//        pVector[i] += v.pVector[i];
//    }
//
//    return *this;
//}



#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector {
protected:
    ValType* pVector; // Указатель на массив элементов
    int Size;         // Размер вектора

public:
    // Конструкторы и деструктор
    TVector(int s = 5); // Конструктор по умолчанию
    TVector(const TVector& v); // Конструктор копирования
    TVector(TVector&& v) noexcept; // Конструктор перемещения
    ~TVector();

    // Методы доступа
    int GetSize() const { return Size; } // Размер вектора

    // Операторы доступа
    ValType& operator[](int pos);
    const ValType& operator[](int pos) const;

    // Операторы сравнения
    bool operator==(const TVector& v) const;
    bool operator!=(const TVector& v) const;

    // Оператор присваивания
    TVector& operator=(TVector v); // Используем идиому copy-and-swap

    // Скалярные операции
    TVector operator+(const ValType& val) const;
    TVector operator-(const ValType& val) const;
    TVector operator*(const ValType& val) const;

    // Векторные операции
    TVector operator+(const TVector& v) const;
    TVector operator-(const TVector& v) const;
    ValType operator*(const TVector& v) const; // Скалярное произведение

    // Оператор +=
    TVector& operator+=(const TVector& v);

    // Ввод-вывод
    friend std::istream& operator>>(std::istream& in, TVector& v) {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TVector& v) {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }

    // Обмен данными между двумя векторами
    friend void swap(TVector& first, TVector& second) noexcept {
        using std::swap;
        swap(first.pVector, second.pVector);
        swap(first.Size, second.Size);
    }
};

// Реализация методов TVector

template <class ValType>
TVector<ValType>::TVector(int s) : Size(s) {
    if (s < 0)
        throw std::invalid_argument("Negative size in TVector constructor");
    if (s > MAX_VECTOR_SIZE)
        throw std::out_of_range("Vector size exceeds maximum allowed size");

    pVector = new ValType[Size](); // Инициализация нулями
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) : Size(v.Size) {
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::TVector(TVector&& v) noexcept
    : pVector(v.pVector), Size(v.Size) {
    v.pVector = nullptr;
    v.Size = 0;
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < 0 || pos >= Size)
        throw std::out_of_range("Index out of range in TVector::operator[]");
    return pVector[pos];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < 0 || pos >= Size)
        throw std::out_of_range("Index out of range in TVector::operator[]");
    return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size)
        return false;

    for (int i = 0; i < Size; ++i) {
        if (pVector[i] != v.pVector[i])
            return false;
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(TVector v) {
    swap(*this, v);
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] += val;
    return tmp;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] -= val;
    return tmp;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] *= val;
    return tmp;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Vectors have different sizes");

    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] += v.pVector[i];
    return tmp;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Vectors have different sizes");

    TVector<ValType> tmp(*this);
    for (int i = 0; i < Size; ++i)
        tmp.pVector[i] -= v.pVector[i];
    return tmp;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Vectors have different sizes");

    ValType scal = ValType();
    for (int i = 0; i < Size; ++i)
        scal += (pVector[i] * v.pVector[i]);
    return scal;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator+=(const TVector& v) {
    if (Size != v.Size)
        throw std::invalid_argument("Vectors must have the same size");

    for (int i = 0; i < Size; ++i) {
        pVector[i] += v.pVector[i];
    }

    return *this;
}











//// Верхнетреугольная матрица
//template <class ValType>
//class TMatrix : public TVector<TVector<ValType>> {
//public:
//    explicit TMatrix(int s = 3);
//    TMatrix(const TMatrix& mt);                    // конструктор копирования
//    TMatrix(TMatrix&& mt) noexcept;                // конструктор перемещения
//    TMatrix(const TVector<TVector<ValType>>& mt);  // преобразование типа
//
//    // Операторы сравнения
//    bool operator==(const TMatrix& mt) const;
//    bool operator!=(const TMatrix& mt) const;
//
//    // Оператор присваивания
//    TMatrix& operator=(TMatrix mt); // используем идиому copy-and-swap
//
//    // Операторы сложения и вычитания
//    TMatrix operator+(const TMatrix& mt) const;
//    TMatrix operator-(const TMatrix& mt) const;
//    TMatrix operator*(const TMatrix<ValType>& mt) const;
//
//    // Ввод-вывод
//    friend std::istream& operator>>(std::istream& in, TMatrix& mt) {
//        for (int i = 0; i < mt.Size; i++)
//            in >> mt.pVector[i];
//        return in;
//    }
//
//    friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {
//        for (int i = 0; i < mt.Size; i++)
//            out << mt.pVector[i] << std::endl;
//        return out;
//    }
//};
//
//// Реализация методов TMatrix
//
//template <class ValType>
//TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
//    if (s > MAX_MATRIX_SIZE || s < 0)
//        throw std::out_of_range("Matrix size exceeds maximum allowed size");
//
//    for (int i = 0; i < this->Size; ++i) {
//        TVector<ValType> buf(this->Size - i, i);
//        this->pVector[i] = buf;
//    }
//}
//
//template <class ValType>
//TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}
//
//template <class ValType>
//TMatrix<ValType>::TMatrix(TMatrix&& mt) noexcept : TVector<TVector<ValType>>(std::move(mt)) {}
//
//template <class ValType>
//TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}
//
//template <class ValType>
//bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
//    if (this->Size != mt.Size)
//        return false;
//    for (int i = 0; i < this->Size; ++i) {
//        if (this->pVector[i] != mt.pVector[i])
//            return false;
//    }
//    return true;
//}
//
//template <class ValType>
//bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
//    return !(*this == mt);
//}
//
//template <class ValType>
//TMatrix<ValType>& TMatrix<ValType>::operator=(TMatrix mt) {
//    swap(*this, mt);
//    return *this;
//}
//
//template <class ValType>
//TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
//    if (this->Size != mt.Size)
//        throw std::invalid_argument("Matrices have different sizes");
//
//    TMatrix<ValType> tmp(*this);
//    for (int i = 0; i < this->Size; ++i)
//        tmp.pVector[i] = this->pVector[i] + mt.pVector[i];
//    return tmp;
//}
//
//template <class ValType>
//TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
//    if (this->Size != mt.Size)
//        throw std::invalid_argument("Matrices have different sizes");
//
//    TMatrix<ValType> tmp(*this);
//    for (int i = 0; i < this->Size; ++i)
//        tmp.pVector[i] = this->pVector[i] - mt.pVector[i];
//    return tmp;
//}
//
//template <class ValType>
//TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix<ValType>& mt) const {
//    if (this->Size != mt.Size)
//        throw std::invalid_argument("Matrices must have the same size for multiplication");
//
//    TMatrix<ValType> result(this->Size);
//
//    for (int i = 0; i < this->Size; ++i) {
//        for (int j = 0; j < this->Size; ++j) {
//            result[i][j] = ValType(0);
//            for (int k = 0; k < this->Size; ++k) {
//                result[i][j] += (*this)[i][k] * mt[k][j];
//            }
//        }
//    }
//
//    return result;
//}

template <class ValType>
class TMatrix : public TVector<TVector<ValType>> {
public:
    explicit TMatrix(int s = 3);
    TMatrix(const TMatrix& mt);                    // Конструктор копирования
    TMatrix(TMatrix&& mt) noexcept;                // Конструктор перемещения
    TMatrix(const TVector<TVector<ValType>>& mt);  // Преобразование типа

    // Операторы сравнения
    bool operator==(const TMatrix& mt) const;
    bool operator!=(const TMatrix& mt) const;

    // Оператор присваивания
    TMatrix& operator=(TMatrix mt); // Используем идиому copy-and-swap

    // Операторы сложения и вычитания
    TMatrix operator+(const TMatrix& mt) const;
    TMatrix operator-(const TMatrix& mt) const;
    TMatrix operator*(const TMatrix<ValType>& mt) const;

    // Ввод-вывод
    friend std::istream& operator>>(std::istream& in, TMatrix& mt) {
        std::cout << "Enter the matrix' size: " << mt.Size << "x" << mt.Size << ":\n";

        for (int i = 0; i < mt.Size; ++i) 
        {
            std::cout << i + 1 << " row: ";
            for (int j = 0; j < mt.Size; ++j) 
            {
                if (j >= i) 
                {                    
                    in >> mt[i][j];
                }
                else 
                {
                    in >> mt[i][j];
                    mt[i][j] = 0;
                }
            }
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {
        for (int i = 0; i < mt.Size; i++) {
            for (int j = 0; j < mt.Size; j++) {
                if (j >= i) {
                    out << mt[i][j] << ' ';
                }
                else {
                    out << "0 ";
                }

                
            }
            out << std::endl;
        }
        return out;
    }
};

// Реализация методов TMatrix

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
    if (s > MAX_MATRIX_SIZE || s < 0)
        throw std::out_of_range("Matrix size exceeds maximum allowed size");

    for (int i = 0; i < this->Size; ++i) {
        TVector<ValType> buf(this->Size); // Создаем строку с уменьшающимся размером
        this->pVector[i] = buf;
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(TMatrix&& mt) noexcept : TVector<TVector<ValType>>(std::move(mt)) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    if (this->Size != mt.Size)
        return false;
    for (int i = 0; i < this->Size; ++i) {
        if (this->pVector[i] != mt.pVector[i])
            return false;
    }
    return true;
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(TMatrix mt) {
    swap(*this, mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    if (this->Size != mt.Size)
        throw std::invalid_argument("Matrices have different sizes");

    TMatrix<ValType> tmp(*this);
    for (int i = 0; i < this->Size; ++i)
        tmp.pVector[i] = this->pVector[i] + mt.pVector[i];
    return tmp;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    if (this->Size != mt.Size)
        throw std::invalid_argument("Matrices have different sizes");

    TMatrix<ValType> tmp(*this);
    for (int i = 0; i < this->Size; ++i)
        tmp.pVector[i] = this->pVector[i] - mt.pVector[i];
    return tmp;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix<ValType>& mt) const {
    if (this->Size != mt.Size)
        throw std::invalid_argument("Matrices must have the same size for multiplication");

    TMatrix<ValType> result(this->Size);

    /*for (int i = 0; i < this->Size; ++i) {
        for (int j = i; j < this->Size; ++j) {
            ValType sum = ValType(0);
            for (int k = i; k <= j; ++k) {
                sum += (*this)[i][k - i] * mt[k][j - k];
            }
            result[i][j - i] = sum;
        }
    }*/

    for (int i = 0; i < this->Size; ++i) {
        for (int j = 0; j < this->Size; ++j) {
            ValType sum = ValType(0);
            for (int k = 0; k < this->Size; ++k)
            {
                sum += (*this)[i][k] * mt[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}




















// Реализация класса для решения матричного уравнения видов AX=B и XA=B
// template <class ValType>
// class MatrixEquationSolver {
// public:
//     // Решение уравнения A * X = B
//     static TMatrix<ValType> SolveAXB(const TMatrix<ValType>& A, const TMatrix<ValType>& B);

//     // Решение уравнения X * A = B
//     static TMatrix<ValType> SolveXAB(const TMatrix<ValType>& A, const TMatrix<ValType>& B);

// private:
//     // Метод для нахождения обратной матрицы
//     static TMatrix<ValType> InverseMatrix(const TMatrix<ValType>& A);

//     // Метод для проверки, является ли матрица квадратной
//     static bool IsSquareMatrix(const TMatrix<ValType>& A);
// };

// // Реализация методов

// template <class ValType>
// bool MatrixEquationSolver<ValType>::IsSquareMatrix(const TMatrix<ValType>& A) {
//     return A.GetSize() == A[0].GetSize();
// }

// template <class ValType>
// TMatrix<ValType> MatrixEquationSolver<ValType>::InverseMatrix(const TMatrix<ValType>& A) {
//     if (!IsSquareMatrix(A))
//         throw std::invalid_argument("Matrix must be square to compute its inverse");

//     int n = A.GetSize();
//     TMatrix<ValType> invA(n); // Создаем матрицу для хранения обратной матрицы
//     TMatrix<ValType> tempA = A; // Создаем копию матрицы A для работы

//     // Инициализация единичной матрицы
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             invA[i][j] = (i == j) ? ValType(1) : ValType(0);
//         }
//     }

//     // Прямой ход метода Гаусса
//     for (int i = 0; i < n; ++i) {
//         // Проверка на нулевой элемент на диагонали
//         if (tempA[i][i] == ValType(0))
//             throw std::runtime_error("Matrix is singular and cannot be inverted");

//         // Нормализация текущей строки
//         ValType diag = tempA[i][i];
//         for (int j = 0; j < n; ++j) {
//             tempA[i][j] /= diag;
//             invA[i][j] /= diag;
//         }

//         // Вычитание текущей строки из остальныхстрок
//         for (int k = 0; k < n; ++k) {
//             if (k != i) {
//                 ValType factor = tempA[k][i];
//                 for (int j = 0; j < n; ++j) {
//                     tempA[k][j] -= factor * tempA[i][j];
//                     invA[k][j] -= factor * invA[i][j];
//                 }
//             }
//         }
//     }

//     return invA;
// }

// template <class ValType>
// TMatrix<ValType> MatrixEquationSolver<ValType>::SolveAXB(const TMatrix<ValType>& A, const TMatrix<ValType>& B) {
//     if (!IsSquareMatrix(A))
//         throw std::invalid_argument("Matrix A must be square");

//     if (A.GetSize() != B.GetSize())
//         throw std::invalid_argument("Matrix A and B must have the same size");

//     TMatrix<ValType> invA = InverseMatrix(A); // Находим обратную матрицу A
//     return invA * B; // Решение X = A^(-1) * B
// }

// template <class ValType>
// TMatrix<ValType> MatrixEquationSolver<ValType>::SolveXAB(const TMatrix<ValType>& A, const TMatrix<ValType>& B) {
//     if (!IsSquareMatrix(A))
//         throw std::invalid_argument("Matrix A must be square");

//     if (A.GetSize() != B.GetSize())
//         throw std::invalid_argument("Matrix A and B must have the same size");

//     TMatrix<ValType> invA = InverseMatrix(A); // Находим обратную матрицу A
//     return B * invA; // Решение X = B * A^(-1)
// }


template <class ValType>
class MatrixEquationSolver {
public:
    // Решение уравнения A * X = B
    static TMatrix<ValType> SolveAXB(const TMatrix<ValType>& A, const TMatrix<ValType>& B);

    // Решение уравнения X * A = B
    static TMatrix<ValType> SolveXAB(const TMatrix<ValType>& A, const TMatrix<ValType>& B);

private:
    static TMatrix<ValType> InverseMatrix(const TMatrix<ValType>& A);
    // Метод для нахождения обратной матрицы (для верхнетреугольных матриц)

    // Проверка, является ли матрица верхнетреугольной и невырожденной
    static bool IsUpperTriangularAndNonSingular(const TMatrix<ValType>& A);

    static bool IsSquareMatrix(const TMatrix<ValType>& A);
};



template <class ValType>
bool MatrixEquationSolver<ValType>::IsUpperTriangularAndNonSingular(const TMatrix<ValType>& A) {
    

    // Проверка, что все элементы ниже главной диагонали равны нулю
    /*for (int i = 0; i < A.GetSize(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[i][j] != ValType()) {
                return false;
            }
        }
    }*/



    // Проверка, что все элементы на главной диагонали ненулевые
    for (int i = 0; i < A.GetSize(); ++i) 
    {
        if (A[i][i] == ValType(0)) 
        {
            return false;
        }
    }

    return true;
}

template <class ValType>
TMatrix<ValType> MatrixEquationSolver<ValType>::InverseMatrix(const TMatrix<ValType>& A) {
    if (!IsUpperTriangularAndNonSingular(A)) {
        throw std::invalid_argument("Matrix is not upper triangular or is singular");
    }

    int n = A.GetSize();
    TMatrix<ValType> invA(n);

    // Инициализация единичной матрицы
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            invA[i][j] = (i == j) ? ValType(1) : ValType(0);
        }
    }

    // Обратная подстановка для нахождения обратной матрицы
    for (int i = n - 1; i >= 0; --i) {
        ValType diag = A[i][i];
        for (int j = 0; j < n; ++j) {
            invA[i][j] /= diag;
        }

        for (int k = i - 1; k >= 0; --k) {
            ValType factor = A[k][i];
            for (int j = 0; j < n; ++j) {
                invA[k][j] -= factor * invA[i][j];
            }
        }
    }

    return invA;
}

template <class ValType>
TMatrix<ValType> MatrixEquationSolver<ValType>::SolveAXB(const TMatrix<ValType>& A, const TMatrix<ValType>& B) {
    if (!IsUpperTriangularAndNonSingular(A)) {
        throw std::invalid_argument("Matrix A is not upper triangular or is singular");
    }

    if (A.GetSize() != B.GetSize()) {
        throw std::invalid_argument("Matrix A and B must have the same size");
    }

    TMatrix<ValType> invA = InverseMatrix(A);
    //std::cout << "Inversed Matrix:" << "\n" << invA << "\n\n\n";
    return invA * B;
}

template <class ValType>
TMatrix<ValType> MatrixEquationSolver<ValType>::SolveXAB(const TMatrix<ValType>& A, const TMatrix<ValType>& B) {
    if (!IsUpperTriangularAndNonSingular(A)) {
        throw std::invalid_argument("Matrix A is not upper triangular or is singular");
    }

    if (A.GetSize() != B.GetSize()) {
        throw std::invalid_argument("Matrix A and B must have the same size");
    }

    TMatrix<ValType> invA = InverseMatrix(A);
    return B * invA;
}