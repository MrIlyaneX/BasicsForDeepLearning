//
// Created by misty on 3/10/2023.
//

#include "../headers/matrix.hpp"

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


//int templates

template Matrix<int>::Matrix();

template Matrix<int>::Matrix(const int row_number, const int column_number);

template Matrix<int>::Matrix(const int &number_square_matrix_);

template Matrix<int>::~Matrix();

template Matrix<int>::Matrix(const Matrix<int> &item);

template Matrix<int>::Matrix(std::initializer_list<std::initializer_list<int>> item);

template pair<int, int> Matrix<int>::size() const;

template int Matrix<int>::operator()(const int row_number, const int column_number) const;

template Matrix<int> &Matrix<int>::operator=(const Matrix<int> &item);

template void Matrix<int>::swap(Matrix<int> &first_matrix_, Matrix<int> &second_matrix_) noexcept;

template Matrix<int> &Matrix<int>::operator+=(const Matrix<int> &item);

template Matrix<int> Matrix<int>::operator+(const Matrix<int> &item);

template Matrix<int> &Matrix<int>::operator-=(const Matrix<int> &item);

template Matrix<int> Matrix<int>::operator-(const Matrix<int> &item);

template Matrix<int> &Matrix<int>::operator*=(const Matrix<int> &item);

template Matrix<int> Matrix<int>::operator*(const Matrix<int> &item);

template Matrix<int> Matrix<int>::operator*(const int &item);

template Matrix<int> &Matrix<int>::operator*=(const int &item);

template Matrix<int> &Matrix<int>::transpose();

template int Matrix<int>::Dot(const Matrix<int> &matrix1);

template Matrix<int>::Matrix(Matrix<int> &&other) noexcept;

template Matrix<int> &Matrix<int>::operator=(Matrix<int> &&other) noexcept;

//float templates

template Matrix<float>::Matrix();

template Matrix<float>::Matrix(const int row_number, const int column_number);

template Matrix<float>::Matrix(const int &number_square_matrix_);

template Matrix<float>::~Matrix();

template Matrix<float>::Matrix(const Matrix<float> &item);

template Matrix<float>::Matrix(std::initializer_list<std::initializer_list<float>> item);

template pair<int, int> Matrix<float>::size() const;

template int Matrix<float>::operator()(const int row_number, const int column_number) const;

template Matrix<float> &Matrix<float>::operator=(const Matrix<float> &item);

template void Matrix<float>::swap(Matrix<float> &first_matrix_, Matrix<float> &second_matrix_) noexcept;

template Matrix<float> &Matrix<float>::operator+=(const Matrix<float> &item);

template Matrix<float> Matrix<float>::operator+(const Matrix<float> &item);

template Matrix<float> &Matrix<float>::operator-=(const Matrix<float> &item);

template Matrix<float> Matrix<float>::operator-(const Matrix<float> &item);

template Matrix<float> &Matrix<float>::operator*=(const Matrix<float> &item);

template Matrix<float> Matrix<float>::operator*(const Matrix<float> &item);

template Matrix<float> Matrix<float>::operator*(const int &item);

template Matrix<float> &Matrix<float>::operator*=(const int &item);

template Matrix<float> &Matrix<float>::transpose();

template float Matrix<float>::Dot(const Matrix<float> &matrix1);

template Matrix<float>::Matrix(Matrix<float> &&other) noexcept;

template Matrix<float> &Matrix<float>::operator=(Matrix<float> &&other) noexcept;

//double templates

template Matrix<double>::Matrix();

template Matrix<double>::Matrix(const int row_number, const int column_number);

template Matrix<double>::Matrix(const int &number_square_matrix_);

template Matrix<double>::~Matrix();

template Matrix<double>::Matrix(const Matrix<double> &item);

template Matrix<double>::Matrix(std::initializer_list<std::initializer_list<double>> item);

template pair<int, int> Matrix<double>::size() const;

template int Matrix<double>::operator()(const int row_number, const int column_number) const;

template Matrix<double> &Matrix<double>::operator=(const Matrix<double> &item);

template void Matrix<double>::swap(Matrix<double> &first_matrix_, Matrix<double> &second_matrix_) noexcept;

template Matrix<double> &Matrix<double>::operator+=(const Matrix<double> &item);

template Matrix<double> Matrix<double>::operator+(const Matrix<double> &item);

template Matrix<double> &Matrix<double>::operator-=(const Matrix<double> &item);

template Matrix<double> Matrix<double>::operator-(const Matrix<double> &item);

template Matrix<double> &Matrix<double>::operator*=(const Matrix<double> &item);

template Matrix<double> Matrix<double>::operator*(const Matrix<double> &item);

template Matrix<double> Matrix<double>::operator*(const int &item);

template Matrix<double> &Matrix<double>::operator*=(const int &item);

template Matrix<double> &Matrix<double>::transpose();

template double Matrix<double>::Dot(const Matrix<double> &matrix1);

template Matrix<double>::Matrix(Matrix<double> &&other) noexcept;

template Matrix<double> &Matrix<double>::operator=(Matrix<double> &&other) noexcept;
