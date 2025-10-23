#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <cassert>

#include "matrix.hpp"
#include "generator.hpp"

constexpr inline double MAX_MATRIX_VALUE = 1e5;
constexpr inline double MAX_ROW_COEF_VALUE = 100;

void matrix_lower_triangle_random_fill(mtx::Matrix<double> &matrix) {
    assert(matrix.n_rows() == matrix.n_cols());

    for (std::size_t i = 0; i < matrix.n_cols(); ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            matrix[j][i] = test::randomDouble(-MAX_MATRIX_VALUE, MAX_MATRIX_VALUE);
        }
    }   
}

void shuffle_matrix(mtx::Matrix<double> &matrix, const double max_abs_row_coef) {
    if (matrix.n_rows() == 1) return;

    for (std::size_t dst_row_idx = 0; dst_row_idx < matrix.n_rows(); ++dst_row_idx) {
        std::size_t source_row_idx = (std::size_t) test::randomInt(0, matrix.n_rows());
        while (source_row_idx == dst_row_idx) {
            source_row_idx = (std::size_t) test::randomInt(0, matrix.n_rows());
        }
        double src_row_coef = test::randomDouble(-max_abs_row_coef, max_abs_row_coef);
        for (std::size_t col_idx = 0; col_idx < matrix.n_cols(); ++col_idx) {
            matrix[dst_row_idx][col_idx] += matrix[source_row_idx][col_idx] * src_row_coef;
        }
    }
}


int main (int argc, char** argv) {
    // argv[1] - size matrix
    // argv[2] - determinant
    if (argc != 3) {
        return 1;
    }

    std::size_t size = atoi(argv[1]);
    double determinant = atof(argv[2]);

    mtx::Matrix<double> matrix = mtx::Matrix<double>::identity(size);
    matrix[0][0] = determinant;

    matrix_lower_triangle_random_fill(matrix);
    shuffle_matrix(matrix, MAX_ROW_COEF_VALUE);

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "\n";
    }
}
