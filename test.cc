#include <gtest/gtest.h>
#include "headers/matrix.hpp"

template<typename T>
class MatrixTester : public Matrix<T> {
public:
    using Matrix<T>::Matrix;

    using Matrix<T>::row_;
    using Matrix<T>::column_;
    using Matrix<T>::matrix_;

    using Matrix<T>::row_by_scalar;
    using Matrix<T>::swap;
    using Matrix<T>::size;

    using Matrix<T>::operator=;
    using Matrix<T>::operator();
    using Matrix<T>::operator[];
    using Matrix<T>::operator+=;
    using Matrix<T>::operator+;
};

// Test Matrix default constructor
TEST(MatrixTester, DefaultConstructor) {
    MatrixTester<int> matrix;
    EXPECT_EQ(matrix.row_, 0);
    EXPECT_EQ(matrix.column_, 0);
    EXPECT_TRUE(matrix.matrix_.empty());
}

// Test Matrix constructor with row, column and default value
TEST(MatrixTester, ConstructorWithRowColumnDefault) {
    MatrixTester<int> matrix(2, 3, 0);
    EXPECT_EQ(matrix.row_, 2);
    EXPECT_EQ(matrix.column_, 3);
    EXPECT_EQ(matrix.matrix_.size(), 2);
    EXPECT_EQ(matrix.matrix_[0].size(), 3);
    EXPECT_EQ(matrix.matrix_[1].size(), 3);
    for (int i = 0; i < matrix.row_; i++) {
        for (int j = 0; j < matrix.column_; j++) {
            EXPECT_EQ(matrix.matrix_[i][j], 0);
        }
    }
}

// Test Matrix copy constructor
TEST(MatrixTester, CopyConstructor) {
    MatrixTester<int> matrix1(2, 3, 0);
    MatrixTester<int> matrix2(matrix1);
    EXPECT_EQ(matrix1.row_, matrix2.row_);
    EXPECT_EQ(matrix1.column_, matrix2.column_);
    EXPECT_EQ(matrix1.matrix_.size(), matrix2.matrix_.size());
    for (int i = 0; i < matrix1.row_; i++) {
        for (int j = 0; j < matrix1.column_; j++) {
            EXPECT_EQ(matrix1.matrix_[i][j], matrix2.matrix_[i][j]);
        }
    }
}

// Test Matrix destructor
TEST(MatrixTester, Destructor) {
    MatrixTester<int> matrix(2, 3, 0);
    matrix.~MatrixTester();
    EXPECT_EQ(matrix.row_, 0);
    EXPECT_EQ(matrix.column_, 0);
    EXPECT_TRUE(matrix.matrix_.empty());
}

// Test constructor from initializer list
TEST(MatrixTester, InitListConstructorTest) {
    MatrixTester<int> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    EXPECT_EQ(matrix.row_, 3);
    EXPECT_EQ(matrix.column_, 3);
    EXPECT_EQ(matrix.matrix_, (std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
}

// Test copy constructor
TEST(MatrixTester, CopyConstructorTest) {
    MatrixTester<int> matrix({{1, 2}, {3, 4}});
    MatrixTester<int> matrix_copy(matrix);
    EXPECT_EQ(matrix_copy.row_, matrix.row_);
    EXPECT_EQ(matrix_copy.column_, matrix.column_);
    EXPECT_EQ(matrix_copy.matrix_, matrix.matrix_);
}

// Test move constructor
TEST(MatrixTester, MoveConstructorTest) {
    MatrixTester<int> matrix({{1, 2}, {3, 4}});
    MatrixTester<int> matrix_move(std::move(matrix));
    EXPECT_EQ(matrix_move.row_, 2);
    EXPECT_EQ(matrix_move.column_, 2);
    EXPECT_EQ(matrix_move.matrix_, (std::vector<std::vector<int>>{{1, 2}, {3, 4}}));
}

// Test move assignment operator
TEST(MatrixTester, MoveAssignmentTest) {
    MatrixTester<int> matrix({{1, 2}, {3, 4}});
    MatrixTester<int> matrix_move({{5, 6}, {7, 8}});
    matrix_move = std::move(matrix);
    EXPECT_EQ(matrix_move.row_, 2);
    EXPECT_EQ(matrix_move.column_, 2);
    EXPECT_EQ(matrix_move.matrix_, (std::vector<std::vector<int>>{{1, 2}, {3, 4}}));
}


// Tests the [] operator for a Matrix<double> object
TEST(MatrixTester, OperatorSquareBrackets) {
    MatrixTester<double> mat(2, 2);
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
    mat[1][0] = 3.0;
    mat[1][1] = 4.0;
    EXPECT_DOUBLE_EQ(mat[1][0], 3.0);
    mat[1][0] = 5.0;
    EXPECT_DOUBLE_EQ(mat[1][0], 5.0);
    EXPECT_THROW(mat[2][2], std::out_of_range);
}

// Test the size() function
TEST(MatrixTester, SizeTest) {
    MatrixTester<int> matrix(2, 3, 0);
    EXPECT_EQ(matrix.size(), std::make_pair(2,3));
}