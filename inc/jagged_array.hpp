#pragma once

#include <algorithm>
#include <utility>

namespace mtx {

template<typename T>
class Array {
  public:
    Array() = default;

    Array(std::size_t size) : size_(size), data_(allocate(size)) {}

    ~Array() { deallocate(data_); }

    Array(const Array& other) : size_(other.size()), data_(allocate(size())) {
        std::copy(other.data(), other.data() + size(), data_);
    }

    Array(Array&& other) {
        std::swap(*this, other)
    }

    Array& operator=(const Array& other) {
        if(this == &other) {
            return *this;
        }

        Array temp(other);
        std::swap(*this, temp);

        return *this;
    }

    Array& operator=(Array&& other) {
        if(this == &other) {
            return *this;
        }

        std::swap(*this, other);

        return *this;
    }

  public:
    std::size_t size() const { return size_; }
    bool empty() const { return size() == 0; }

  private:
    T* data() { return data_; } 
    const T* data() const { return data_; } 

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
    std::size_t size_ = 0;
    T* data_{};
};

template<typename T, typename Iter>
// requires std::same_as<std::iter_value_t<ContainerIter>, T>
class JaggedArray {
  public:
    JaggedArray() = default;

    JaggedArray(std::size_t n_rows, Iter sizes_begin, Iter sizes_end) {}
    JaggedArray(std::size_t n_rows, Iter sizes_begin, Iter sizes_end, Iter elems_begin, Iter elems_end) {}

    JaggedArray(std::size_t n_rows, std::size_t n_cols) {}
    JaggedArray(std::size_t n_rows, std::size_t n_cols, Iter elems_begin, Iter elems_end) {}

  public:
    bool empty() const { return data_.empty(); }
    bool is_rectangular() const { return is_rectangular; }

  public:
    std::size_t n_rows() const {
        return data_.size();
    }

    std::size_t n_cols() const requires (is_rectangular() && !empty()) {
        return data_[0].size();
    }

  private:
    Array<Array<T>> data_{};
    bool is_rectangular = false;
};

}; // namespace mtx
