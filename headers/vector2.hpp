//
// Created by misty on 3/10/2023.
//

#ifndef DL_VECTOR2_HPP
#define DL_VECTOR2_HPP

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class vector2 {
private:
    int size_;
    bool transposed;
    vector<T> vector_;

public:
    vector2();

    explicit vector2(int size);

    vector2(const vector2 &item);

    ~vector2();

    int Dot(const vector2 &item);

    int operator()(int element_number) const;

    vector2<T> &operator=(const vector2<T> &item);

    void swap(vector2<T> &first_vector2_, vector2<T> &second_vector2_) noexcept;

    vector2<T> &operator+=(const vector2<T> &item);

    vector2<T> operator+(const vector2<T> &item);

    vector2<T> &operator-=(const vector2<T> &item);

    vector2<T> operator-(const vector2<T> &item);

    vector2<T> &operator*=(const vector2<T> &item);

    vector2<T> operator*(const vector2<T> &item);

    vector2<T> &operator*=(const int &item);

    vector2<T> operator*(const int &item);

    friend ostream &operator<<(ostream &output_stream, const vector2<T> &item) {
        for (int i = 0; i < item.size_; i++) {
            output_stream << item.vector_[i] << " ";
        }
        output_stream << "\n";
        return output_stream;
    }

    friend istream &operator>>(istream &input_stream, vector2<T> &item) {
        for (int i = 0; i < item.size_; i++) {
            input_stream >> item.vector_[i];
        }
        return input_stream;
    }
};


#endif //DL_VECTOR2_HPP
