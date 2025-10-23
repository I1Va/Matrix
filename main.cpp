#include <iostream>

#include <matrix.hpp>

int main () {
    mtx::Matrix<double> mtx = mtx::Matrix<double>::identity(5);
    std:: cout << mtx << '\n' << std::endl;;

    mtx.swap_rows(0, 4);

    std::cout << mtx << std::endl;
}
