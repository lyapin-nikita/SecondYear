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


   
    std::cout << "Enter matrix A:" << "\n";
    std::cin >> A;
    std::cout << A << "\n\n\n";

    
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