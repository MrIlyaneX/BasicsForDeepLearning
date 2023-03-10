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

#endif //DL_MATRIX_HPP
