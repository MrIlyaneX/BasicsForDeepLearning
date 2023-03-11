#include <cassert>
#include "headers/matrix.hpp"

int main() {

    {
        Identity<int> a;

        std::cout << a;
    }

    //c-tors and assignments
    {
        int n = 2, default_val = 2;

        //default c-tor
        Matrix<int> a(n, n, default_val);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert(a(i, j) == default_val);
            }
        }

        //list init
        Matrix<int> b = {{0, 1}, {1, 2}};

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; ++j) {
                assert(b(i, j) == i + j);
            }
        }

        //assignment
        b = a;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert(a(i, j) == b(i, j));
            }
        }
    }

    //overloaded operations, such as + - * [] and [][]
    {
        int n = 2, default_val = 2, m = 10;

        //default c-tor
        Matrix<int> a(n, n, default_val);
        Matrix<int> b(n, n, default_val);
        Matrix<int> c(n, m);
        Matrix<int> d(m, n);
        Matrix<int> tmp;

        //+ operators
        tmp = a + b;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert(tmp(i, j) == (a(i, j) + b(i, j)));
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert((a + b)(i, j) == (a(i, j) + b(i, j)));
            }
        }

        //- operators
        tmp = a - b;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert(tmp(i, j) == (a(i, j) - b(i, j)));
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                assert((a - b)(i, j) == (a(i, j) - b(i, j)));
            }
        }

        //* operators

        tmp = a * b;

        tmp = c * d;

        Matrix<int> q = {{0, 1}, {1, 2}, {3, 4}};

        for (int i : q[0]) {
            std::cout << i << " ";
        }

        q[0][0] = 2;
        q[0] = std::vector<int>(2, 1);
    }

    //Matrix operations -> Transpose, Dot(for vector-based matrix)
    {
        Matrix<int> a = {{0, 1}, {1, 2}, {3, 4}};
        Matrix<int> b = a.Transpose();
        a.Transpose();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                assert(a(i, j) == b(j, i));
            }
        }

        //Dot and * of vectors
        Matrix<int> c = {{1, 2, 3, 4}};
        Matrix<int> d = {{1, 2, 3, 4}};
        assert(c.Dot(d) == 30);
        c.Transpose();

        Matrix<int> tmp{{30}};
        assert(d * c == tmp);

        c.Transpose();
        d.Transpose();
        assert(c * d == tmp);

    }

    //Gaussian Implementations, Inverse, Solve Systems
    {

    }

    return 0;
}
