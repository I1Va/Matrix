#pragma once

#include "jaggedArray.hpp"

// Поля
// double cached determinant


// namespace mtx;
// T determinant() const


// mult

namespace mtx 
{


    template<typename T>
    concept FloatingPoint = std::floating_point<T>;

    template <FloatingPoint T>
    class Matrix {
        std::size_t rows_ = 0
        std::size_t cols_ = 0;
    
        JaggedArray<T> data_;


      public: // Constructors
    
        template<typename ContainerIter>
        requires std::same_as<std::iter_value_t<ContainerIter>, T>
        
        explicit Matrix(const std::size_t n): 
            rows_(n), cols_(n), JaggedArray(n, n) {}

        Matrix(const std::size_t rows, const std::size_t cols): 
            rows_(rows), cols_(cols), JaggedArray(rows, cols) {}

        Matrix(ContainerIter fst, ContainerIter snd, const std::size_t rows, const std::size_t cols): 
            rows_(rows), cols_(cols), JaggedArray(fst, snd, rows, cols) {}


        static Matrix<T> eye(const std::size_t n) {
            Matrix<T> eye_matrix(n, n);
            for (std::size_t i = 0; i < n; i++)
                eye_matrix[i][i] = T(1.0);
            
            return eye_matrix;
        }

      public: // Operators
    
        Array<T> &operator[](const std::size_t idx) {
            return data_[idx];
        }

        const Array<T> &operator[](const std::size_t idx) const {
            return data_[idx];
        }

      public: // Math
    
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
    }
}