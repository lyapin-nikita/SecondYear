#include <iostream>
#include "Monom.h"
#include "Polynom.h"
using namespace std;

int main() {
    try {
        // Testing polynomial creation
        std::cout << "=== Polynomial Creation ===" << std::endl;
        Polynom p1, p2;

        std::cout << "Enter first polynomial (e.g., 2x1^2 - 3x2 + x1x2^3 + 5): ";
        std::cin >> p1;
        std::cout << "Polynomial 1: ";
        p1.Print();

        std::cout << "\nEnter second polynomial (e.g., x1^2 + 2x2 - x1x2^2): ";
        std::cin >> p2;
        std::cout << "Polynomial 2: ";
        p2.Print();

        // Testing addition
        std::cout << "\n=== Polynomial Addition ===" << std::endl;
        Polynom sum = p1 + p2;
        std::cout << "p1 + p2 = ";
        sum.Print();

        // Testing subtraction
        std::cout << "\n=== Polynomial Subtraction ===" << std::endl;
        Polynom diff = p1 - p2;
        std::cout << "p1 - p2 = ";
        diff.Print();

        // Testing multiplication
        std::cout << "\n=== Polynomial Multiplication ===" << std::endl;
        Polynom prod = p1 * p2;
        std::cout << "p1 * p2 = ";
        prod.Print();

        // Testing scalar multiplication
        std::cout << "\n=== Scalar Multiplication ===" << std::endl;
        double scalar;
        std::cout << "Enter scalar value: ";
        std::cin >> scalar;
        Polynom scaled = p1 * scalar;
        std::cout << "p1 * " << scalar << " = ";
        scaled.Print();

        // Testing polynomial division
        std::cout << "\n=== Polynomial Division ===" << std::endl;
        try {
            std::tuple<Polynom, Polynom> division_result = p1 / p2;
            Polynom quotient = std::get<0>(division_result);
            Polynom remainder = std::get<1>(division_result);
            std::cout << "Quotient (p1 / p2) = ";
            quotient.Print();
            std::cout << "Remainder (p1 / p2) = ";
            remainder.Print();
        }
        catch (const std::exception& e) {
            std::cout << "Division error: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}