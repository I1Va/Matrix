#pragma once

#include "common.hpp"
#include "jagged_array.hpp"


namespace mtx 
{

template <FloatingPoint T>
class Matrix {
  public: // Constructors
    template<typename Iter>
    requires std::same_as<std::iter_value_t<Iter>, T>
    
    explicit Matrix(const std::size_t n): 
        n_rows_(n), n_cols(n), JaggedArray(n, n) {}

    Matrix(const std::size_t n_rows, const std::size_t n_cols): 
        n_rows_(n_rows), n_cols_(n_cols), JaggedArray(n_rows, n_cols) {}

    Matrix(const std::size_t n_rows_, const std::size_t n_cols, Iter elems_begin, Iter elems_end): 
        n_rows_(n_rows), n_cols(n_cols), JaggedArray(n_rows, n_cols, elems_begin, elems_end) {}

    static Matrix<T> diag(const std::size_t n, const T value) {
        Matrix<T> eye_matrix(n, n);
        for (std::size_t i = 0; i < n; i++)
            eye_matrix[i][i] = value;
        
        return eye_matrix;
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

    Matrix& transpose()& {
        for (std::size_t i = 0; i < n_rows_; i++) {
            for (std::size_t j = 0; j < i; j++) {
                std::swap(data_[i][j], data_[j][i]);
            }
        }

        return *this;
    };

    void swap_rows(const std::size_t fst, const std::size_t snd) {
        std::swap(data_[fst], data_[_snd]);
    }
    
    double abs_max_in_col(const std::size_t col, const std::size_t fst, const std::size_t snd) const {
        T result = 0;
        for (std::size_t i = fst; i < snd; i++) {
            result = std::fmax(result, data_[i][col]);
        }
        return result;
    }

    void add_row_to_row(const std::size_t dst, const std::size_t src, const T mul=T(1.0)) {
        for (std::size_t i = 0; i < n_cols_; i++) {
            data_[dst][i] += data_[src][i] * mul;
        }
    }

    T determinant() const;

  public: // Getters
    std::size_t n_rows() const { return n_rows_; }
    std::size_t n_cols() const { return n_cols_; } 

  private:
    std::size_t n_rows_ = 0
    std::size_t n_cols_ = 0;
    JaggedArray<T> data_;
}

} // namespace mtx
