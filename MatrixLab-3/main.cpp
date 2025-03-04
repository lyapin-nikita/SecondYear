#include "utmatrix.h"
#include <iostream>

//func main for testing matrix
int main(void)
{
    TMatrix<int> test1;
    std::cout << test1 << "\n\n\n";

    TMatrix<double> A(3);
    TMatrix<double> B(3);

    // Заполнение матриц A и B (только верхнетреугольные элементы)
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;  // Первая строка: индексы 0, 1, 2
    A[1][1] = 4; A[1][2] = 5;               // Вторая строка: индексы 1, 2
    A[2][2] = 6;                             // Третья строка: индекс 2

    B[0][0] = 1; B[0][1] = 0; B[0][2] = 0;  // Первая строка: индексы 0, 1, 2
    B[1][1] = 1; B[1][2] = 0;               // Вторая строка: индексы 1, 2
    B[2][2] = 1;                            // Третья строка: индекс 2

    try {
        // Решение уравнения A * X = B
        TMatrix<double> X1 = MatrixEquationSolver<double>::SolveAXB(A, B);
        std::cout << "Solution for A * X = B:\n" << X1 << std::endl;

        // Решение уравнения X * A = B
        TMatrix<double> X2 = MatrixEquationSolver<double>::SolveXAB(A, B);
        std::cout << "Solution for X * A = B:\n" << X2 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}