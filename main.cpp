#include <iostream>

#include "headers/matrix.hpp"

using namespace std;

int main() {
    Matrix<int> a = {
        {1, 2, 2},
        {3, 4},
        {2, 33, 01, 22}
    };

   Matrix<int> b(std::move(a));

    for (int x : b) {
        cout << x << " ";
    }


    return 0;
}
