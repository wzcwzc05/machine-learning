#include <iostream>
#include <matrix.hpp>
using namespace mt;
int main() {
    std::vector<std::vector<double>> X = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    MMatrix<double> A(X);
    std::cout << "A = " << std::endl;
    A.print();
    std::cout << "A^T = " << std::endl;
    A.transpose().print();
    std::cout << "det(A)=" << std::endl;
    std::cout << A.det() << std::endl;
    return 0;
}