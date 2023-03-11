//
// Created by misty on 3/10/2023.
//

#ifndef DL_MATRIX_HPP
#define DL_MATRIX_HPP

#pragma once

#include <iostream>
#include <vector>
#include <concepts>
#include <iterator>

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

//--------------------
// TODO: Implement Resize (currently do not resize column_ size)
//--------------------

//--------------------
// TODO: Implement Const Iterator
//--------------------

//--------------------
// TODO: Gaussian Eliminations
//--------------------

//--------------------
// TODO: Identity Matrix
//--------------------

//--------------------
// TODO: A = LU and A = LDU factorization
//--------------------

//--------------------
// TODO: Gradient counting
//--------------------



//--------------------
// TODO: Square Matrix (different functional)
//--------------------

//--------------------
// TODO: Identity Matrix (different functional)
//--------------------

//Matrix class is a class that presents 2d matrix and operations over it.
//Matrix supports types of std::is_arithmetic_v<T>
template<typename T> requires Numeric<T>
class Matrix {
public:

    //Default ctor. creates 0*0 matrix
    Matrix();

    //Create row_number*column_number matrix filled with 0's
    [[maybe_unused]] Matrix(int row_number, int column_number, T default_value = 0);

    //Create square number_square_matrix_*number_square_matrix_ matrix filled with 0's
    explicit Matrix(const int &number_square_matrix_);

    //cope ctor
    Matrix(const Matrix<T> &item);

    //move ctor
    Matrix(Matrix<T> &&other) noexcept;

    //move assignment
    Matrix<T> &operator=(Matrix<T> &&other) noexcept;

    //std::initializer_list ctor
    Matrix(std::initializer_list<std::initializer_list<T>> matrix);

    //d-ctor
    ~Matrix();

    //returns std::pair<int,int> of n*m matrix size
    [[nodiscard]] std::pair<int, int> size() const;

    //return element of matrix[row_number][column_number]
    T operator()(int row_number, int column_number) const;

    //assignment operator
    Matrix<T> &operator=(const Matrix<T> &item);

    //swap function. swaps two obj. of class Matrix
    void swap(Matrix<T> &first_matrix_, Matrix<T> &second_matrix_) noexcept;

    Matrix<T> &operator+=(const Matrix<T> &item);

    Matrix<T> operator+(const Matrix<T> &item);

    Matrix<T> &operator-=(const Matrix<T> &item);

    Matrix<T> operator-(const Matrix<T> &item);

    Matrix<T> &operator*=(const Matrix<T> &item);

    Matrix<T> operator*(const Matrix<T> &item);

    Matrix<T> &operator*=(const int &item);

    Matrix<T> operator*(const int &item);

    bool operator==(const Matrix<T> &item);

    //overloaded ostream operator
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &item) {
        for (const auto &row : item.matrix_) {
            std::copy(row.begin(), row.end(), std::ostream_iterator<T>(os, " "));
            os << '\n';
        }
        return os;
    }

    //overloaded istream operator
    friend std::istream &operator>>(std::istream &input_stream, Matrix<T> &item) {
        for (auto &row : item.matrix_) {
            for (auto &elem : row) {
                input_stream >> elem;
            }
        }
        if (!input_stream) {
            throw std::runtime_error("Invalid input (matrix input error)\n");
        }
        return input_stream;
    }

    Matrix<T> &Transpose();

    //Dot product. Works if the matrices as of 1d vector size
    T Dot(const Matrix<T> &matrix1);

    void Resize(int new_row_size, int new_col_size);

    //own iterator class for running through the Matrix out of class.
    class iterator {
    public:
        //default c-tor
        iterator(std::vector<std::vector<T>> &data, int row, int col) : data_(data), row_(row), col_(col) {}

        //dereference operator
        T &operator*() const {
            return data_[row_][col_];
        }

        //for pointer-access operator
        T *operator->() const {
            return &(data_[row_][col_]);
        }

        //increment operator
        iterator &operator++() {
            ++col_;
            if (col_ == data_[row_].size()) {
                ++row_;
                col_ = 0;
            }
            return *this;
        }

        //increment operator
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator &operator--() {
            if (col_ != 0 || row_ != 0) {
                if (col_ != 0) {
                    --col_;
                } else {
                    col_ = data_[--row_].size();
                }
            }
            return *this;
        }

        //increment operator
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        //operator==
        bool operator==(const iterator &other) const {
            return (row_ == other.row_ && col_ == other.col_);
        }

        //operator!=
        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

    private:
        std::vector<std::vector<T>> &data_;
        int row_;
        int col_;
    };

    iterator begin() {
        return iterator(matrix_, 0, 0);
    }

    iterator end() {
        return iterator(matrix_, matrix_.size(), 0);
    }

protected:

    int row_{};
    int column_{};
    std::vector<std::vector<T>> matrix_{};

    //swap rows
    void exchange_rows_(int row1, int row2);

    //swap columns
    void exchange_columns_(int col1, int col2);

};

template<typename T>
requires Numeric<T>
Matrix<T>::Matrix() : row_(0), column_(0), matrix_(column_) {}

template<typename T>
requires Numeric<T>
[[maybe_unused]] Matrix<T>::Matrix(const int row_number, const int column_number, T default_value)
    : row_(row_number), column_(column_number),
      matrix_(row_, std::vector<T>(column_, default_value)) {}

template<typename T>
requires Numeric<T>
Matrix<T>::Matrix(const int &number_square_matrix_) : row_(number_square_matrix_), column_(number_square_matrix_),
                                                      matrix_(row_, std::vector<T>(column_, T())) {}

template<typename T>
requires Numeric<T>
Matrix<T>::~Matrix() {
    matrix_ = std::vector<std::vector<T>>(0);
}

template<typename T>
requires Numeric<T>
Matrix<T>::Matrix(const Matrix<T> &item) : row_(item.row_), column_(item.column_) {
    matrix_.resize(row_, std::vector<T>(column_, T()));
    for (int i = 0; i < item.row_; i++) {
        for (int j = 0; j < item.column_; ++j) {
            matrix_[i][j] = item.matrix_[i][j];
        }
    }
}

template<typename T>
requires Numeric<T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept {
    matrix_ = std::move(other.matrix_);
    row_ = other.row_;
    column_ = other.column_;
    other.row_ = 0;
    other.column_ = 0;
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept {
    if (this == &other) return *this;

    matrix_ = other.matrix_;
    row_ = other.row_;
    column_ = other.column_;

    other.matrix_ = std::move(other.matrix_);
    other.row_ = 0;
    other.column_ = 0;

    return *this;
}

template<typename T>
requires Numeric<T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> list) {
    matrix_.reserve(list.size());
    int mx{};
    int mn{};
    for (const auto &element : list) {
        std::vector<T> tmp;
        tmp.reserve(element.size());
        for (const auto &element2 : element) {
            tmp.push_back(element2);
        }
        mx = ((mx < tmp.size()) ? tmp.size() : mx);
        mn = ((mn > tmp.size()) ? tmp.size() : mn);
        matrix_.push_back(std::move(tmp));
    }
    if (mx != mn) {
        for (auto &element : matrix_) element.resize(mx);
    }
    row_ = matrix_.size();
    column_ = matrix_[0].size();
}

template<typename T>
requires Numeric<T>
[[nodiscard]] std::pair<int, int> Matrix<T>::size() const {
    return std::pair<int, int>{row_, column_};
}

template<typename T>
requires Numeric<T>
T Matrix<T>::operator()(const int row_number, const int column_number) const {
    return matrix_[row_number][column_number];
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &item) {
    Matrix tmp(item);
    swap(tmp, *this);
    return *this;
}

template<typename T>
requires Numeric<T>
void Matrix<T>::swap(Matrix<T> &first_matrix_, Matrix<T> &second_matrix_) noexcept {
    std::swap(first_matrix_.matrix_, second_matrix_.matrix_);
    std::swap(first_matrix_.row_, second_matrix_.row_);
    std::swap(first_matrix_.column_, second_matrix_.column_);
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &item) {
    if (item.size() == size()) {
        Matrix tmp_matrix_(*this);
        for (int i = 0; i < item.row_; i++) {
            for (int j = 0; j < item.column_; ++j) {
                tmp_matrix_.matrix_[i][j] += item.matrix_[i][j];
            }
        }
        swap(tmp_matrix_, *this);
    }
    return *this;
}

template<typename T>
requires Numeric<T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ += item;
    return tmp_matrix_;
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &item) {
    if (item.size() == size()) {
        Matrix tmp_matrix_(*this);
        for (int i = 0; i < item.row_; i++) {
            for (int j = 0; j < item.column_; ++j) {
                tmp_matrix_.matrix_[i][j] -= item.matrix_[i][j];
            }
        }
        swap(tmp_matrix_, *this);
    }
    return *this;
}

template<typename T>
requires Numeric<T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ -= item;
    return tmp_matrix_;
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &item) {
    if (column_ == item.row_) {
        Matrix tmp_matrix_(row_, item.column_);
        for (int i = 0; i < row_; i++) {
            for (int k = 0; k < item.row_; k++) {
                for (int j = 0; j < item.column_; j++) {
                    tmp_matrix_.matrix_[i][j] += (matrix_[i][k] * item.matrix_[k][j]);
                }
            }
        }
        swap(tmp_matrix_, *this);
    }
    return *this;
}

template<typename T>
requires Numeric<T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ *= item;
    return tmp_matrix_;
}

template<typename T>
requires Numeric<T>
Matrix<T> Matrix<T>::operator*(const int &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ *= item;
    return tmp_matrix_;
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::operator*=(const int &item) {
    Matrix tmp_matrix_(*this);
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < column_; ++j) {
            tmp_matrix_.matrix_[i][j] *= item;
        }
    }
    swap(tmp_matrix_, *this);
    return *this;
}

template<typename T>
requires Numeric<T>
Matrix<T> &Matrix<T>::Transpose() {
    Matrix tmp_matrix_(column_, row_);
    for (int i = 0; i < column_; i++) {
        for (int j = 0; j < row_; ++j) {
            tmp_matrix_.matrix_[i][j] = matrix_[j][i];
        }
    }
    swap(tmp_matrix_, *this);
    return *this;
}

template<typename T>
requires Numeric<T>
T Matrix<T>::Dot(const Matrix<T> &matrix1) {
    if (matrix1.size() == size()) {
        if (matrix1.column_ == 1 && column_ == 1) {
            int dot = 0;
            int n = matrix1.row_;
            for (int i = 0; i < n; i++) dot += matrix1.matrix_[i][0] * matrix_[i][0];
            return dot;
        }
        if (matrix1.row_ == 1 && row_ == 1) {
            int dot = 0;
            int n = matrix1.column_;
            for (int i = 0; i < n; i++) dot += matrix1.matrix_[0][i] * matrix_[0][i];
            return dot;
        }
    }

    throw std::runtime_error("Wrong size of matrices for using Dot (product)");

}

template<typename T>
requires Numeric<T>
void Matrix<T>::exchange_rows_(int row1, int row2) {
    std::swap(matrix_[row1], matrix_[row2]);
}

template<typename T>
requires Numeric<T>
void Matrix<T>::exchange_columns_(int col1, int col2) {
    for (int i = 0; i < row_; ++i) {
        std::swap(matrix_[i][col1], matrix_[i][col2]);
    }
}

template<typename T>
requires Numeric<T>
void Matrix<T>::Resize(int new_row_size, int new_col_size) {
    matrix_.resize(new_row_size, std::vector<T>(new_col_size, T()));
    row_ = new_row_size;
    column_ = new_col_size;
}

template<typename T>
requires Numeric<T>
bool Matrix<T>::operator==(const Matrix<T> &item) {
    if (size() == item.size()) {
        for (int i = 0; i < row_; i++) {
            for (int j = 0; j < column_; ++j) {
                if (matrix_[i][j] != item.matrix_[i][j]) return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

#endif //DL_MATRIX_HPP
