#include <iostream>

#include <matrix.hpp>
#include <vector>
#include <Eigen/Dense>


void scan_matrix(const std::size_t n, std::vector<std::vector<double>> &matrix) {
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
}

double get_eigen_determinant(const std::size_t n, const std::vector<std::vector<double>> &input_matrix) {
    Eigen::MatrixXd A(n, n); 

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            A(i, j) = input_matrix[i][j];
        }
    }

    return A.determinant();
}

double get_our_determinant(const std::size_t n, const std::vector<std::vector<double>> &input_matrix) {
    mtx::Matrix<double> A(n, n);

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            A[i][j] = input_matrix[i][j];
        }
    }

    return A.determinant();
}

int main () {
    std::size_t n = 0;
    std::cin >> n;

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    scan_matrix(n, matrix);

    std::cout << "eigen : " << get_eigen_determinant(n, matrix) << '\n';
    std::cout << "our   : " << get_our_determinant  (n, matrix) << '\n';
}