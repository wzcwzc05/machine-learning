#include <matrix.hpp>
namespace mt {
template <typename T>
MMatrix<T> MMatrix<T>::cdot(const MMatrix<T> &a) {
    MMatrix<T> res(a.rows(), a.cols());
    if (a.rows() != this->cols() || this->rows() != a.cols())
        throw std::invalid_argument(
            "Matrix dimensions do not match for dot product");
    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = 0;
            for (int k = 0; k < this->cols(); k++) {
                res(i, j) += (*this)(i, k) * a(k, j);
            }
        }
    }
    return res;
}
template <typename T>
void MMatrix<T>::print() {
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
};  // namespace mt