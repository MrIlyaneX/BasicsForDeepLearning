//
// Created by misty on 3/10/2023.
//

#include "../headers/vector2.hpp"


template<typename T>
vector2<T>::vector2() : size_(0), transposed(false) {}

template<typename T>
vector2<T>::vector2(const int size) : size_(size), transposed(false), vector_{size, T()} {}

template<typename T>
vector2<T>::~vector2() {
    std::destroy(vector_.begin(), vector_.end());
}

template<typename T>
vector2<T>::vector2(const vector2 &item) : size_(item.size_), transposed(item.transposed), vector_(item.vector_) {}

template<typename T>
int vector2<T>::Dot(const vector2 &item) {
    int ans = 0;
    if (size_ == item.size_) {
        for (int i = 0; i < size_; i++) ans += item.vector_[i] * vector_[i];
        return ans;
    }
}

template<typename T>
int vector2<T>::operator()(int element_number) const {
    if (element_number >= 0 && element_number < size_) return vector_[element_number];
}

template<typename T>
vector2<T> &vector2<T>::operator=(const vector2<T> &item) {
    vector2 tmp(item);
    swap(tmp, *this);
    return *this;
}

template<typename T>
void vector2<T>::swap(vector2<T> &first_vector2_, vector2<T> &second_vector2_) noexcept {
    std::swap(first_vector2_.vector_, second_vector2_.vector_);
    std::swap(first_vector2_.size_, second_vector2_.size_);
    std::swap(first_vector2_.transposed, second_vector2_.transposed);
}

template<typename T>
vector2<T> &vector2<T>::operator+=(const vector2<T> &item) {
    return *this;
}

template<typename T>
vector2<T> vector2<T>::operator+(const vector2<T> &item) {
    vector2 tmp_vector2_(*this);
    tmp_vector2_ += item;
    return tmp_vector2_;
}

template<typename T>
vector2<T> &vector2<T>::operator-=(const vector2<T> &item) {
    return *this;
}

template<typename T>
vector2<T> vector2<T>::operator-(const vector2<T> &item) {
    vector2 tmp_vector2_(*this);
    tmp_vector2_ -= item;
    return tmp_vector2_;
}

template<typename T>
vector2<T> &vector2<T>::operator*=(const vector2<T> &item) {
//    if (size_ == item.size_) {
//        vector2 tmp_vector2_(row_, item.column_);
//        for (int i = 0; i < row_; i++) {
//            for (int k = 0; k < item.row_; k++) {
//                for (int j = 0; j < item.column_; j++) {
//                    tmp_vector2_.matrix_[i][j] += (matrix_[i][k] * item.matrix_[k][j]);
//                }
//            }
//        }
//        swap(tmp_matrix_, *this);
//    }
    return *this;
}

template<typename T>
vector2<T> vector2<T>::operator*(const vector2<T> &item) {
    vector2 tmp_vector2_(*this);
    tmp_vector2_ *= item;
    return tmp_vector2_;
}

template<typename T>
vector2<T> &vector2<T>::operator*=(const int &item) {
    for (int i = 0; i < size_; i++) vector_[i] *= item;
    return *this;
}

template<typename T>
vector2<T> vector2<T>::operator*(const int &item) {
    vector2 tmp_vector2_(*this);
    tmp_vector2_ *= item;
    return tmp_vector2_;
}


//int templates

template vector2<int>::vector2();

//template vector2<int>::vector2(const int row_number, const int column_number);
//
//template vector2<int>::vector2(const int &number_square_vector2_);

template vector2<int>::~vector2();

template vector2<int>::vector2(const vector2<int> &item);

//template pair<int, int> vector2<int>::size() const;

template int vector2<int>::operator()(int element_number) const;

template vector2<int> &vector2<int>::operator=(const vector2<int> &item);

template void vector2<int>::swap(vector2<int> &first_vector2_, vector2<int> &second_vector2_) noexcept;

template vector2<int> &vector2<int>::operator+=(const vector2<int> &item);

template vector2<int> vector2<int>::operator+(const vector2<int> &item);

template vector2<int> &vector2<int>::operator-=(const vector2<int> &item);

template vector2<int> vector2<int>::operator-(const vector2<int> &item);

template vector2<int> &vector2<int>::operator*=(const vector2<int> &item);

template vector2<int> vector2<int>::operator*(const vector2<int> &item);

template vector2<int> vector2<int>::operator*(const int &item);

template vector2<int> &vector2<int>::operator*=(const int &item);

//float templates

template vector2<float>::vector2();

//template vector2<float>::vector2(const int row_number, const int column_number);
//
//template vector2<float>::vector2(const int &number_square_vector2_);

template vector2<float>::~vector2();

template vector2<float>::vector2(const vector2<float> &item);

//template pair<int, int> vector2<float>::size() const;

template int vector2<float>::operator()(int element_number) const;

template vector2<float> &vector2<float>::operator=(const vector2<float> &item);

template void vector2<float>::swap(vector2<float> &first_vector2_, vector2<float> &second_vector2_) noexcept;

template vector2<float> &vector2<float>::operator+=(const vector2<float> &item);

template vector2<float> vector2<float>::operator+(const vector2<float> &item);

template vector2<float> &vector2<float>::operator-=(const vector2<float> &item);

template vector2<float> vector2<float>::operator-(const vector2<float> &item);

template vector2<float> &vector2<float>::operator*=(const vector2<float> &item);

template vector2<float> vector2<float>::operator*(const vector2<float> &item);

template vector2<float> vector2<float>::operator*(const int &item);

template vector2<float> &vector2<float>::operator*=(const int &item);


//double templates

template vector2<double>::vector2();

//template vector2<double>::vector2(const int row_number, const int column_number);

//template vector2<double>::vector2(const int &number_square_vector2_);

template vector2<double>::~vector2();

template vector2<double>::vector2(const vector2<double> &item);

//template pair<int, int> vector2<double>::size() const;

template int vector2<double>::operator()(int element_number) const;

template vector2<double> &vector2<double>::operator=(const vector2<double> &item);

template void vector2<double>::swap(vector2<double> &first_vector2_, vector2<double> &second_vector2_) noexcept;

template vector2<double> &vector2<double>::operator+=(const vector2<double> &item);

template vector2<double> vector2<double>::operator+(const vector2<double> &item);

template vector2<double> &vector2<double>::operator-=(const vector2<double> &item);

template vector2<double> vector2<double>::operator-(const vector2<double> &item);

template vector2<double> &vector2<double>::operator*=(const vector2<double> &item);

template vector2<double> vector2<double>::operator*(const vector2<double> &item);

template vector2<double> vector2<double>::operator*(const int &item);

template vector2<double> &vector2<double>::operator*=(const int &item);



