#include <iostream>

#include "headers/matrix.hpp"

using namespace std;

int main() {
    Matrix<int> a = {
        {1, 2, 2},
        {3, 4},
        {2, 33, 01, 22}
    };

   // Matrix<int> b(std::move(a));

    Matrix<int> b = std::move(a);



    cout << b;

    return 0;
}
