#include <iostream>
#include <matrix.hpp>
using namespace mt;
int main() {
    MMatrix<double> A(2, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    // A.print();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}