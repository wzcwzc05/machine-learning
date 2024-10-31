#pragma once
#include <cmath>
#include <iostream>
#include <vector>
namespace mt {
template <typename T>
class MMatrix {
   public:
    int rows_ = 0, cols_ = 0;
    T *data_ = nullptr;
    MMatrix(int rows, int cols)
        : rows_(rows), cols_(cols) {  // 构造函数，创建矩阵
        data_ = new double[rows * cols];
    }
    MMatrix(const MMatrix &other)
        : rows_(other.rows_), cols_(other.cols_) {  // 拷贝构造函数
        data_ = new double[rows_ * cols_];
        for (int i = 0; i < rows_ * cols_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    MMatrix(std::vector<std::vector<T>> &data)  // 构造函数，从二维数组构造矩阵
        : rows_(data.size()), cols_(data[0].size()) {
        data_ = new double[rows_ * cols_];
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i * cols_ + j] = data[i][j];
            }
        }
    }
    MMatrix(int rows, int cols, T val) : rows_(rows), cols_(cols) {
        this->data_ = new T[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            this->data_[i] = val;
        }
    }
    ~MMatrix() { delete[] data_; }
    T &operator()(int i,
                  int j) {  // 重载()运算符，获取元素值，i表示行，j表示列
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
            throw "Index out of range";
        }
        return data_[i * cols_ + j];
    }
    int rows() const;
    int cols() const;
    MMatrix<T> operator+(const MMatrix &a);  // 矩阵加法（元素相加）
    MMatrix<T> operator*(const MMatrix &a);  // 矩阵乘法（元素相乘）
    MMatrix<T> operator-(const MMatrix &a);  // 矩阵减法（元素相减）
    MMatrix<T> operator/(const MMatrix &a);  // 矩阵除法（元素相除）
    MMatrix<T> cdot(const MMatrix &a);       // 矩阵点乘
    MMatrix<T> transpose();                  // 矩阵转置
    MMatrix<T> inverse();                    // 矩阵求逆
    double det();                         // 矩阵行列式
    MMatrix<T> submatrix(int i, int j);      // 子矩阵
    MMatrix<T> submatrix(int i, int j, int rows,
                      int cols);     // 从第i行第j列提取rows行cols列的子矩阵
    MMatrix<T> minor(int i, int j);     // 矩阵的第i行第j列的余子式
    MMatrix<T> cofactor(int i, int j);  // 矩阵的第i行第j列的代数余子式
    MMatrix<T> adjoint();               // 矩阵的伴随矩阵
    T trace();                 // 矩阵的迹
    void print();                    // 打印矩阵
    void set(int i, int j, T val);   // 设置元素值
    T get(int i, int j) const;       // 获取元素值
};
};  // namespace mt
#include "matrix.cpp"