#pragma once

#include <algorithm>
#include <utility>
#include <iostream>

namespace mtx {

template<typename Iter, typename T>
concept IteratorOf = std::same_as<std::iter_value_t<Iter>, T>;

template<typename T>
class Array {
  public:
    Array() = default;

    Array(std::size_t size, const T& value) {
        reallocate_and_fill(size, value);
    }

    Array(std::initializer_list<T> init_list) : size_(init_list.size()) {
        data_ = allocate(size());

        std::copy(init_list.begin(), init_list.end(), data_);
    }

    explicit Array(std::size_t size) : Array(size, T{}) {}

    ~Array() { deallocate(data_); }

    Array(const Array& other) : size_(other.size()), data_(allocate(size())) {
        std::copy(other.begin(), other.end(), data_);
    }

    Array(Array&& other) {
        swap(other);
    }

    Array& operator=(const Array& other) {
        if(this == &other) {
            return *this;
        }

        Array temp(other);
        swap(temp);

        return *this;
    }

    Array& operator=(Array&& other) {
        if(this == &other) {
            return *this;
        }

        swap(other);

        return *this;
    }

  public:
    std::size_t size() const { return size_; }
    bool empty() const { return size() == 0; }

    T* begin() { return data_; } 
    const T* begin() const { return data_; } 

    T* end() { return begin() + size(); } 
    const T* end() const { return begin() + size(); } 

  public:
    T& operator[](std::size_t idx) { return data_[idx]; }
    const T& operator[](std::size_t idx) const { return data_[idx]; }

  public:
    void resize(std::size_t new_size, const T& value) {
        reallocate_and_fill(new_size, value);
    }

    void resize(std::size_t new_size) {
        reallocate_and_fill(new_size, T{});
    }

  private:
    void swap(Array& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    static T* allocate(std::size_t capacity) {
        return new T[capacity];
    }
    static void deallocate(T* data) {
        delete[] data;
    }

    void reallocate(std::size_t new_size) {
        if (new_size == size()) {
            return;
        }

        T* new_buffer = allocate(new_size);

        if (begin() != nullptr) {
            std::size_t n_to_copy = std::min(size_, new_size);
            std::copy(begin(), begin() + n_to_copy, new_buffer);
            deallocate(data_);
        }

        data_ = new_buffer;
        size_ = new_size;
    }

    void reallocate_and_fill(std::size_t new_size, const T& value) {
        std::size_t old_size = size();

        reallocate(new_size);

        T* first = begin() + old_size;
        T* last  = begin() + new_size;

        if (last > first) {
            std::fill(first, last, value);
        }
    }

  private:
    std::size_t size_ = 0;
    T* data_ = nullptr;
};

template<typename T>
inline std::ostream& operator<<(std::ostream& ostream, const Array<T>& array) {
    for (auto it = array.begin(); it != array.end(); ++it) {
        if (it != array.begin()) {
            ostream << ", ";
        }

        ostream << *it;
    }

    return ostream;
}

template<typename T>
class JaggedArray {
  public:
    JaggedArray() = default;

    JaggedArray(std::size_t n_rows, std::size_t rows_size) : data_(n_rows) {
        for (std::size_t row_idx = 0; row_idx < n_rows; ++row_idx) {
            data_[row_idx].resize(rows_size);
        }
    }

    template<typename Iter>
    requires IteratorOf<Iter, std::size_t>
    JaggedArray(std::size_t n_rows, Iter rows_sizes_begin, Iter rows_sizes_end) : data_(n_rows) {
        auto size_it = rows_sizes_begin;

        for (std::size_t row_idx = 0; row_idx < n_rows; ++row_idx, ++size_it) {
            data_[row_idx].resize(*size_it);
        }
    }

    template<typename Iter1, typename Iter2>
    requires IteratorOf<Iter1, std::size_t> && IteratorOf<Iter2, T>
    JaggedArray(std::size_t n_rows, Iter1 rows_sizes_begin, Iter1 rows_sizes_end, Iter2 elems_begin, Iter2 elems_end) 
        : JaggedArray(n_rows, rows_sizes_begin, rows_sizes_end)
    {    
        auto elem_it = elems_begin;

        for (std::size_t row_idx = 0; row_idx < n_rows; ++row_idx) {
            for (std::size_t col_idx = 0; col_idx < data_[row_idx].size(); ++col_idx, ++elem_it) {
                data_[row_idx][col_idx] = *elem_it;
            }
        }
    }

    JaggedArray(std::initializer_list<std::initializer_list<T>> init_lists) 
        : data_(init_lists.size()) 
    {
        std::size_t row_idx = 0;
        for (const auto& row_list : init_lists) {
            data_[row_idx].resize(row_list.size());
            std::copy(row_list.begin(), row_list.end(), data_[row_idx].begin());
            ++row_idx;
        }
    }

  public:
    Array<T>& operator[](std::size_t idx) {
        return data_[idx];
    }

    const Array<T>& operator[](std::size_t idx) const {
        return data_[idx];
    }

  public:
    Array<T>* begin() { return data_.begin(); } 
    const Array<T>* begin() const { return data_.begin(); } 

    Array<T>* end() { return data_.end(); } 
    const Array<T>* end() const { return data_.end(); } 

    bool empty() const { return data_.empty(); }

    std::size_t n_rows() const {
        return data_.size();
    }

    void resize(std::size_t new_size) {
        data_.resize(new_size);
    }

    void resize_row(std::size_t row_idx, std::size_t new_size) {
        data_[row_idx].resize(new_size);
    }

    void swap_rows(std::size_t first_idx, std::size_t second_idx) {
        std::swap(data_[first_idx], data_[second_idx]);
    }

  private:
    Array<Array<T>> data_{};
};

template<typename T>
inline std::ostream& operator<<(std::ostream& ostream, const JaggedArray<T>& array) {
    for (auto it = array.begin(); it != array.end(); ++it) {
        if (it != array.begin()) {
            ostream << "\n";
        }

        ostream << *it;
    }

    return ostream;
}

template<typename T>
class RectangularArray : public JaggedArray<T> {
  public:
    RectangularArray() = default;

    RectangularArray(std::size_t n_rows, std::size_t n_cols) 
        : JaggedArray<T>(n_rows, Array<std::size_t>(n_rows, n_cols)) {}

    template<typename Iter>
    requires IteratorOf<Iter, T>
    RectangularArray(std::size_t n_rows, std::size_t n_cols, Iter elems_begin, Iter elems_end) 
        : JaggedArray<T>(n_rows, n_cols, elems_begin, elems_end) {}

    RectangularArray(std::initializer_list<std::initializer_list<T>> init_lists)
        : JaggedArray<T>(init_lists) {}
    
  public:
    using JaggedArray<T>::operator[];

  public:  
    using JaggedArray<T>::n_rows;

    std::size_t n_cols() const {
        if (this->empty()) {
            return 0;
        }
        
        return (*this)[0].size();
    }

    using JaggedArray<T>::empty;
    using JaggedArray<T>::swap_rows;
};

}; // namespace mtx
