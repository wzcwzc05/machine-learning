#pragma once
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
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::transpose() {
    MMatrix<T> res(this->cols(), this->rows());
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            res(j, i) = (*this)(i, j);
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::submatrix(int i, int j, int rows, int cols) {
    MMatrix<T> res(rows, cols);
    for (int k = 0; k < rows; k++) {
        for (int l = 0; l < cols; l++) {
            res(k, l) = (*this)(i + k, j + l);
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::submatrix(int i, int j) {
    MMatrix<T> res(this->rows() - i, this->cols() - j);
    for (int k = 0; k < res.rows(); k++) {
        for (int l = 0; l < res.cols(); l++) {
            res(k, l) = (*this)(i + k, j + l);
        }
    }
    return std::move(res);
}
template <typename T>
double MMatrix<T>::det() {
    if (this->rows() != this->cols())
        throw std::invalid_argument("Matrix is not square for determinant");
    if (this->rows() == 1) return (*this)(0, 0);
    if (this->rows() == 2)
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    double res = 0;
    for (int j = 0; j < this->cols(); j++) {
        res += (*this)(0, j) * cofactor(0, j).det();
    }
    return res;
}
template <typename T>
T MMatrix<T>::trace() {
    if (this->rows() != this->cols())
        throw std::invalid_argument("Matrix is not square for trace");
    T res = 0;
    for (int i = 0; i < this->rows(); i++) {
        res += (*this)(i, i);
    }
    return res;
}
template <typename T>
MMatrix<T> MMatrix<T>::operator/(const MMatrix<T> &a) {
    if (this->rows() != a.rows() || this->cols() != a.cols())
        throw std::invalid_argument(
            "Matrix dimensions do not match for division");
    MMatrix<T> res(a.rows(), a.cols());
    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = (*this)(i, j) / a(i, j);
        }
    }
    return std::move(res);
}

template <typename T>
MMatrix<T> MMatrix<T>::operator+(const MMatrix<T> &a) {
    if (this->rows() != a.rows() || this->cols() != a.cols())
        throw std::invalid_argument(
            "Matrix dimensions do not match for addition");
    MMatrix<T> res(a.rows(), a.cols());
    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = (*this)(i, j) + a(i, j);
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::operator-(const MMatrix<T> &a) {
    if (this->rows() != a.rows() || this->cols() != a.cols())
        throw std::invalid_argument(
            "Matrix dimensions do not match for subtraction");
    MMatrix<T> res(a.rows(), a.cols());
    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            res(i, j) = (*this)(i, j) - a(i, j);
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::operator*(const MMatrix<T> &a) {
    if (this->cols() != a.cols() && this->rows() != a.rows())
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication");
    MMatrix<T> res(this->rows(), this->cols());
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            res(i, j) = (*this)(i, j) * a(i, j);
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::minor(int x, int y) {
    MMatrix<T> res(this->rows() - 1, this->cols() - 1);
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            if (i == x || j == y) continue;
            res(i < x ? i : i - 1, j < y ? j : j - 1) = (*this)(i, j);
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::cofactor(int x, int y) {
    MMatrix<T> res(this->rows() - 1, this->cols() - 1);
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++) {
            if (i == x || j == y) continue;
            res(i < x ? i : i - 1, j < y ? j : j - 1) =
                (*this)(i, j) * ((i + j) % 2 == 0 ? 1 : -1);
        }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::adjoint() {
    if (this->rows() != this->cols())
        throw std::invalid_argument("Matrix is not square for adjoint");
    MMatrix<T> res(this->rows(), this->cols());
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            res(i, j) = cofactor(i, j).det();
        }
    }
    return std::move(res);
}
template <typename T>
MMatrix<T> MMatrix<T>::inverse() {
    if (this->rows() != this->cols())
        throw std::invalid_argument("Matrix is not square for inverse");
    if (this->rows() == 1) return MMatrix<T>(1, 1, 1 / (*this)(0, 0));
    MMatrix<T> res(this->rows(), this->cols());
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            res(i, j) = cofactor(i, j).det();
        }
    }
    return res.transpose() / det();
}
template <typename T>
void MMatrix<T>::set(int i, int j, T val) {
    (*this)(i, j) = val;
}
template <typename T>
T MMatrix<T>::get(int i, int j) const {
    return (*this)(i, j);
}
template <typename T>
int MMatrix<T>::rows() const {
    return this->rows_;
}
template <typename T>
int MMatrix<T>::cols() const {
    return this->cols_;
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