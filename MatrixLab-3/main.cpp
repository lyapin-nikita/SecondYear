#include "utmatrix.h"
#include <iostream>










//тестирование
int main(void)
{
    //TMatrix<int> test1;
    //std::cout << test1 << "\n\n\n";

    TMatrix<double> A(3); 
    TMatrix<double> B(3); 
    std::cout << A << "\n\n\n";
    std::cout << B << "\n\n\n";


   //Заполнение верхнетреугольной матрицы A
    /*A[0][0] = 2; A[0][1] = 3; A[0][2] = 1;
    A[1][1] = 4; A[1][2] = 5;
    A[2][2] = 6;*/
    std::cout << "Enter matrix A:" << "\n";
    std::cin >> A;
    std::cout << A << "\n\n\n";

    ////Заполнение матрицы B
    //B[0][0] = 1; B[0][1] = 0; B[0][2] = 0;
    //B[1][1] = 1; B[1][2] = 0;
    //B[2][2] = 1;
    std::cout << "Enter matrix B:" << "\n";
    std::cin >> B;
    std::cout << B << "\n\n\n";

    try
    {
        //A*X =B
        TMatrix<double> X1 = MatrixEquationSolver<double>::SolveAXB(A, B);
        std::cout << "Solution for A * X = B:\n" << X1 << std::endl;

        //X*A = B
        TMatrix<double> X2 = MatrixEquationSolver<double>::SolveXAB(A, B);
        std::cout << "Solution for X * A = B:\n" << X2 << std::endl;

    }
    catch (const std::exception& trouble)
    {
        std::cerr << "Error: " << trouble.what();
    }
    
    
    
    

    return 0;
}