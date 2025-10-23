#pragma once

#include <algorithm>
#include <utility>

namespace mtx {

template<typename T>
class Array {
  public:
    Array() = default;

    Array(std::size_t capacity) : capacity_(capacity), data_(allocate(capacity)) {}

    ~Array() { deallocate(data_); }

    Array(const Array& other) : capacity_(other.capacity()), data_(allocate(capacity())) {
        std::copy(other.data(), other.data() + capacity(), data_);
    }

    Array(Array&& other) {
        std::swap(other)
    }

    Array& operator=(const Array& other) {
        if(this == &other) {
            return *this;
        }

        Array temp(other);
        std::swap(temp);

        return *this;
    }

    Array& operator=(Array&& other) {
        if(this == &other) {
            return *this;
        }

        std::swap(other);

        return *this;
    }

  public:
    T* data() { return data_; } 
    const T* data() const { return data_; } 
    std::size_t capacity() const { return capacity_; }

  public:
    T& operator[](std::size_t idx) { return data_[idx]; }
    const T& operator[](std::size_t idx) const { return data_[idx]; }

  private:
    static T* allocate(std::size_t capacity) {
        return new T[capacity];
    }
    static void deallocate(T* data) {
        delete[] data;
    }

  private:
    std::size_t capacity_ = 0;
    T* data_{};
};

// template<typename T, typename Iter>
// // requires std::same_as<std::iter_value_t<ContainerIter>, T>
// class JaggedArray {
//   public:
//     JaggedArray() = default;
//     JaggedArray(std::size_t n_rows, std::size_t n_cols) {}
//     JaggedArray(std::size_t n_rows, Iter sizes_begin, Iter sizes_end) {}


//   private:
//     Array* data_;
//     std::size_t n_rows_;
// };

};
