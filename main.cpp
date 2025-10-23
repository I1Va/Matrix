#include <iostream>
#include <vector>

#include <matrix.hpp>

int main () {
    mtx::Matrix<double> mtx(2, 2);
    mtx[0][0] = 1.5;
    mtx[0][1] = 2.0;
    mtx[1][0] = 3.0;
    mtx[1][1] = 4.0;

    std::cout << mtx.determinant() << std::endl;
}
