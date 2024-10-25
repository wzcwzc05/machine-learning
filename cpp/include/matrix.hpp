#include <cmath>
#include <vector>
#include <iostream>
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
    ~MMatrix() { delete[] data_; }
    T &operator()(int i,
                  int j) {  // 重载()运算符，获取元素值，i表示行，j表示列
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
            throw "Index out of range";
        }
        return data_[i * cols_ + j];
    }
    // Matrix &operator=(const Matrix &other);  // 拷贝赋值运算符
    // Matrix operator+(const Matrix &a,
    //                  const Matrix &b);  // 矩阵加法（元素相加）
    // Matrix operator*(const Matrix &a,
    //                  const Matrix &b);  // 矩阵乘法（元素相乘）
    // Matrix operator-(const Matrix &a,
    //                  const Matrix &b);  // 矩阵减法（元素相减）
    // Matrix operator/(const Matrix &a,
    //                  const Matrix &b);  // 矩阵除法（元素相除）
    MMatrix cdot(const MMatrix &a);   // 矩阵点乘
    MMatrix transpose();              // 矩阵转置
    MMatrix inverse();                // 矩阵求逆
    double determinant();             // 矩阵行列式
    MMatrix submatrix(int i, int j);  // 子矩阵
    MMatrix submatrix(int i, int j, int rows,
                      int cols);  // 从第i行第j列提取rows行cols列的子矩阵
    MMatrix minor(int i, int j);    // 矩阵的第i行第j列的余子式
    double cofactor(int i, int j);  // 矩阵的第i行第j列的代数余子式
    MMatrix adjoint();              // 矩阵的伴随矩阵
    MMatrix trace();                // 矩阵的迹
    void print();                   // 打印矩阵
    void set(int i, int j, T val);  // 设置元素值
    T get(int i, int j) const;      // 获取元素值
};
};  // namespace mt