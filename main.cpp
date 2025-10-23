#include <iostream>
#include <vector>

#include <matrix.hpp>

int main () {
    mtx::Matrix<double> mtx = {{1, 1, 1}, {1, 3, 4}, {2, 5, 1}};

    mtx.resize(5, 5);
    std:: cout << mtx << '\n' << std::endl;;

    // mtx.swap_rows(0, 1);

    // std::cout << mtx << std::endl;
}
