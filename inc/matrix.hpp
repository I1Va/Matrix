#pragma once

#include <cassert>
#include <cmath>
#include <algorithm>

#include "common.hpp"
#include "jagged_array.hpp"

namespace mtx {

template <FloatingPoint T>
class Matrix {
  public: // constructors    
    explicit Matrix(const std::size_t size) : data_(size, size) {}

    Matrix(const std::size_t n_rows, const std::size_t n_cols) : data_(n_rows, n_cols) {}

    template<typename Iter>
    requires IteratorOf<Iter, T>
    Matrix(const std::size_t n_rows, const std::size_t n_cols, Iter elems_begin, Iter elems_end) 
        : data_(n_rows, n_cols, elems_begin, elems_end) {}

    Matrix(std::initializer_list<std::initializer_list<T>> init_lists)
        : RectangularArray<T>(init_lists) {}

    static Matrix<T> diag(const std::size_t size, const T value) {
        Matrix<T> diag_matrix(size, size);
        for (std::size_t i = 0; i < size; i++)
            diag_matrix[i][i] = value;
        
        return diag_matrix;
    }

    static Matrix<T> identity(const std::size_t size) {
        return diag(size, T(1.0));
    }

  public: // getters
    std::size_t n_rows() const { return data_.n_rows(); }
    std::size_t n_cols() const { return data_.n_cols(); } 
    const RectangularArray<T> data() const { return data_; }

  public: // operators
    Array<T>& operator[](const std::size_t idx) {
        return data_[idx];
    }

    const Array<T>& operator[](const std::size_t idx) const {
        return data_[idx];
    }

  public: // math
    Matrix<T>& negate() {
        for (std::size_t i = 0; i < n_rows(); i++) {
            for (std::size_t j = 0; j < n_cols(); j++) {
                data_[i][j] *= T(-1.0);
            }
        }

        return *this;
    }

    Matrix<T> transpose() const {
        Matrix<T> res_matrix(n_cols, n_rows);
        for (std::size_t i = 0; i < n_rows(); i++) {
            for (std::size_t j = 0; j < n_cols(); j++) {
                res_matrix[i][j] = data_[j][i];
            }
        }

        return res_matrix;
    };

    void swap_rows(const std::size_t fst_idx, const std::size_t snd_idx) {
        data_.swap_rows(fst_idx, snd_idx);
    }

    T determinant() const;

  private: // determinant details

    std::size_t find_row_with_max_abs_value_in_column_range(const std::size_t column, const std::size_t start_row, const std::size_t end_row) const {
        assert(column < n_cols());
        assert(start_row < n_rows() && end_row < n_rows());
        assert(start_row < end_row);

        std::size_t result_row_idx = start_row;
        T result_value = std::fabs(data_[start_row][column]);

        for (std::size_t row_idx = start_row; row_idx < end_row; row_idx++) {
            T cur_val = std::fabs(data_[row_idx][column]);
            
            if (cur_val > result_value) {
                result_value = cur_val;
                result_row_idx = row_idx;
            }
        }
    
        return result_row_idx;
    }

    void add_row_to_row(const std::size_t dst_row_idx, const std::size_t src_row_idx, const T mul = T(1.0)) {
        assert(dst_row_idx < n_rows());
        assert(src_row_idx < n_rows());
    
        for (std::size_t col_idx = 0; col_idx < n_cols(); col_idx++) {
            data_[dst_row_idx][col_idx] += data_[src_row_idx][col_idx] * mul;
        }
    }

  private: // fields
    RectangularArray<T> data_{};
};

template<FloatingPoint T>
std::ostream& operator<<(std::ostream& ostream, const Matrix<T>& matrix) {
    ostream << matrix.data();

    return ostream;
}

} // namespace mtx
