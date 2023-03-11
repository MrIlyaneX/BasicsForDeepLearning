//
// Created by misty on 3/10/2023.
//

#ifndef DL_MATRIX_HPP
#define DL_MATRIX_HPP

#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
 private:

  int row_{};
  int column_{};
  vector<vector<T>> matrix_{};
 public:

  Matrix();

  [[maybe_unused]] Matrix(int row_number, int column_number);

  explicit Matrix(const int &number_square_matrix_);

  Matrix(const Matrix<T> &item);

  Matrix(Matrix<T> &&other) noexcept;

  Matrix<T> &operator=(Matrix<T> && other) noexcept;

  Matrix(initializer_list<std::initializer_list<T>> matrix);

  ~Matrix();

  [[nodiscard]] pair<int, int> size() const;

  int operator()(int row_number, int column_number) const;

  Matrix<T> &operator=(const Matrix<T> &item);

  void swap(Matrix<T> &first_matrix_, Matrix<T> &second_matrix_) noexcept;

  Matrix<T> &operator+=(const Matrix<T> &item);

  Matrix<T> operator+(const Matrix<T> &item);

  Matrix<T> &operator-=(const Matrix<T> &item);

  Matrix<T> operator-(const Matrix<T> &item);

  Matrix<T> &operator*=(const Matrix<T> &item);

  Matrix<T> operator*(const Matrix<T> &item);

  Matrix<T> &operator*=(const int &item);

  Matrix<T> operator*(const int &item);

  friend ostream &operator<<(ostream &output_stream, const Matrix<T> &item) {
    for (int i = 0; i < item.row_; i++) {
      for (int j = 0; j < item.column_; ++j) {
        output_stream << item.matrix_[i][j] << " ";
      }
      output_stream << "\n";
    }
    return output_stream;
  }

  friend istream &operator>>(istream &input_stream, Matrix<T> &item) {
    for (int i = 0; i < item.row_; i++) {
      for (int j = 0; j < item.column_; ++j) {
        input_stream >> item.matrix_[i][j];
      }
    }
    return input_stream;
  }

  Matrix<T> &transpose();

  T Dot(const Matrix<T> &matrix1);

};

template<typename T>
Matrix<T>::Matrix() : row_(0), column_(0), matrix_(column_) {}

template<typename T>
[[maybe_unused]] Matrix<T>::Matrix(const int row_number, const int column_number)
    : row_(row_number), column_(column_number),
      matrix_(row_, vector<T>(column_, T())) {}

template<typename T>
Matrix<T>::Matrix(const int &number_square_matrix_) : row_(number_square_matrix_), column_(number_square_matrix_),
                                                      matrix_(row_, vector<T>(column_, T())) {}

template<typename T>
Matrix<T>::~Matrix() {
    matrix_ = vector<vector<T>>(0);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &item) : row_(item.row_), column_(item.column_) {
    matrix_.resize(row_, vector<T>(column_, T()));
    for (int i = 0; i < item.row_; i++) {
        for (int j = 0; j < item.column_; ++j) {
            matrix_[i][j] = item.matrix_[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept {
    matrix_ = std::move(other.matrix_);
    row_ = other.row_;
    column_ = other.column_;
    other.row_ = 0;
    other.column_ = 0;
}

template<typename T>
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
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> list) {
    matrix_.reserve(list.size());
    int mx{};
    int mn{};
    for (const auto& element : list ) {
        vector<T> tmp;
        tmp.reserve(element.size());
        for (const auto& element2 : element) {
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
[[nodiscard]] pair<int, int> Matrix<T>::size() const {
    return pair<int, int>{row_, column_};
}

template<typename T>
int Matrix<T>::operator()(const int row_number, const int column_number) const {
    return matrix_[row_number][column_number];
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &item) {
    Matrix tmp(item);
    swap(tmp, *this);
    return *this;
}

template<typename T>
void Matrix<T>::swap(Matrix<T> &first_matrix_, Matrix<T> &second_matrix_) noexcept {
    std::swap(first_matrix_.matrix_, second_matrix_.matrix_);
    std::swap(first_matrix_.row_, second_matrix_.row_);
    std::swap(first_matrix_.column_, second_matrix_.column_);
}

template<typename T>
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
Matrix<T> Matrix<T>::operator+(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ += item;
    return tmp_matrix_;
}

template<typename T>
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
Matrix<T> Matrix<T>::operator-(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ -= item;
    return tmp_matrix_;
}

template<typename T>
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
Matrix<T> Matrix<T>::operator*(const Matrix<T> &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ *= item;
    return tmp_matrix_;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const int &item) {
    Matrix tmp_matrix_(*this);
    tmp_matrix_ *= item;
    return tmp_matrix_;
}

template<typename T>
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
Matrix<T> &Matrix<T>::transpose() {
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
T Matrix<T>::Dot(const Matrix<T> &matrix1) {
    if (matrix1.column_ == 1 && column_ == 1 && matrix1.size() == size()) {
        int dot = 0;
        int n = matrix1.row_;
        for (int i = 0; i < n; i++) dot += matrix1.matrix_[i][0] * matrix_[i][0];
        return dot;
    }
}

#endif //DL_MATRIX_HPP
