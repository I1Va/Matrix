#pragma once

#include "common.hpp"
#include "jaggedArray.hpp"

namespace mtx 
{

template <FloatingPoint T>
class Matrix {
  public: // Constructors
    template<typename Iter>
    requires std::same_as<std::iter_value_t<Iter>, T>
    
    explicit Matrix(const std::size_t n): 
        rows_(n), cols_(n), JaggedArray(n, n) {}

    Matrix(const std::size_t rows, const std::size_t cols): 
        rows_(rows), cols_(cols), JaggedArray(rows, cols) {}

    Matrix(Iter elems_begin, Iter elems_end, const std::size_t rows, const std::size_t cols): 
        rows_(rows), cols_(cols), JaggedArray(rows, cols, elems_begin, elems_end) {}

    static Matrix<T> diag(const std::size_t n, const T value) {
        Matrix<T> eye_matrix(n, n);
        for (std::size_t i = 0; i < n; i++)
            eye_matrix[i][i] = value;
        
        return eye_matrix;
    }

    static Matrix<T> eye(const std::size_t n) {
        return diag(n, T(1.0));
    }

  public: // Operators
    Array<T> &operator[](const std::size_t idx) {
        return data_[idx];
    }

    const Array<T> &operator[](const std::size_t idx) const {
        return data_[idx];
    }

  public: // Math
    Matrix<T>& negate() & {
        for (std::size_t i = 0; i < rows_; i++) {
            for (std::size_t j = 0; j < cols_; j++) {
                data_[i][j] *= T(-1.0);
            }
        }

        return *this;
    }

    Matrix& transpose() & {
        for (std::size_t i = 0; i < rows_; i++) {
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
        for (std::size_t i = 0; i < cols_; i++) {
            data_[dst][i] += data_[src][i] * mul;
        }
    }

    T determinant() const;

  private:
    std::size_t rows_ = 0
    std::size_t cols_ = 0;
    JaggedArray<T> data_;
}

} // namespace mtx
