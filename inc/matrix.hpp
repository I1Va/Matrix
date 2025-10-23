#pragma once

#include <cassert>
#include "common.hpp"
#include "jagged_array.hpp"


namespace mtx 
{

template <FloatingPoint T>
class Matrix {
  public: // Constructors    
    explicit Matrix(const std::size_t n): 
        n_rows_(n), n_cols(n), JaggedArray(n, n) {}

    Matrix(const std::size_t n_rows, const std::size_t n_cols): 
        n_rows_(n_rows), n_cols_(n_cols), JaggedArray(n_rows, n_cols) {}

    template<typename Iter>
    requires std::same_as<std::iter_value_t<Iter>, T>
    Matrix(const std::size_t n_rows_, const std::size_t n_cols, Iter elems_begin, Iter elems_end): 
        n_rows_(n_rows), n_cols(n_cols), JaggedArray(n_rows, n_cols, elems_begin, elems_end) {}

    static Matrix<T> diag(const std::size_t n, const T value) {
        Matrix<T> diag_matrix(n, n);
        for (std::size_t i = 0; i < n; i++)
            diag_matrix[i][i] = value;
        
        return diag_matrix;
    }

    static Matrix<T> identity(const std::size_t n) {
        return diag(n, T(1.0));
    }

  public: // Operators
    Array<T>& operator[](const std::size_t idx) {
        return data_[idx];
    }

    const Array<T>& operator[](const std::size_t idx) const {
        return data_[idx];
    }

  public: // Math
    Matrix<T>& negate()& {
        for (std::size_t i = 0; i < n_rows_; i++) {
            for (std::size_t j = 0; j < n_cols_; j++) {
                data_[i][j] *= T(-1.0);
            }
        }

        return *this;
    }

    Matrix<T> transpose() const {
        Matrix<T> res_matrix(n_cols, n_rows);
        for (std::size_t i = 0; i < n_rows_; i++) {
            for (std::size_t j = 0; j < n_cols_; j++) {
                res_matrix[i][j] = data_[j][i];
            }
        }

        return *this;
    };

    T determinant() const;

  public: // Getters
    std::size_t n_rows() const { return n_rows_; }
    std::size_t n_cols() const { return n_cols_; } 

  private: // determinant details
   void swap_rows(const std::size_t fst, const std::size_t snd) {
        assert(fst < n_cols_ && snd < n_cols_);
        std::swap(data_[fst], data_[_snd]);
    }
    
    std::size_t find_abs_max_row_in_col(const std::size_t col, const std::size_t fst, const std::size_t snd) const {
        assert(col < n_cols_ && fst < n_rows_ && snd < n_rows_);

        std::pair<std::size_t, T> max_res = {fst, data_[fst][col]};
        for (std::size_t i = fst; i < snd; i++) {
            T cur_val =  std::fabs(data_[i][col]);
            if (cur_val > max_res.second) max_res = {i, cur_val};
        }
    
        return max_res;
    }

    void add_row_to_row(const std::size_t dst, const std::size_t src, const T mul=T(1.0)) {
        assert(dst < n_cols_ && src < n_cols_);
    
        for (std::size_t i = 0; i < n_cols_; i++)
            data_[dst][i] += data_[src][i] * mul;
    }

  private:
    std::size_t n_rows_ = 0;
    std::size_t n_cols_ = 0;
    JaggedArray<T> data_;
}

} // namespace mtx
