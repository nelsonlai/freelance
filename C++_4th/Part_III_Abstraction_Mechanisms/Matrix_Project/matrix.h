#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <initializer_list>
#include <memory>
#include <type_traits>

namespace matrix {

// Forward declarations
template<typename T, size_t N>
class Matrix;

template<typename T, size_t N>
class MatrixIterator;

template<typename T, size_t N>
class ConstMatrixIterator;

// Matrix iterator implementation
template<typename T, size_t N>
class MatrixIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
private:
    Matrix<T, N>* matrix_;
    size_t index_;
    
public:
    MatrixIterator(Matrix<T, N>* matrix, size_t index) 
        : matrix_(matrix), index_(index) {}
    
    reference operator*() const {
        return (*matrix_)[index_];
    }
    
    pointer operator->() const {
        return &(*matrix_)[index_];
    }
    
    MatrixIterator& operator++() {
        ++index_;
        return *this;
    }
    
    MatrixIterator operator++(int) {
        MatrixIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    MatrixIterator& operator--() {
        --index_;
        return *this;
    }
    
    MatrixIterator operator--(int) {
        MatrixIterator temp = *this;
        --(*this);
        return temp;
    }
    
    MatrixIterator& operator+=(difference_type n) {
        index_ += n;
        return *this;
    }
    
    MatrixIterator& operator-=(difference_type n) {
        index_ -= n;
        return *this;
    }
    
    MatrixIterator operator+(difference_type n) const {
        return MatrixIterator(matrix_, index_ + n);
    }
    
    MatrixIterator operator-(difference_type n) const {
        return MatrixIterator(matrix_, index_ - n);
    }
    
    difference_type operator-(const MatrixIterator& other) const {
        return index_ - other.index_;
    }
    
    reference operator[](difference_type n) const {
        return (*matrix_)[index_ + n];
    }
    
    bool operator==(const MatrixIterator& other) const {
        return matrix_ == other.matrix_ && index_ == other.index_;
    }
    
    bool operator!=(const MatrixIterator& other) const {
        return !(*this == other);
    }
    
    bool operator<(const MatrixIterator& other) const {
        return index_ < other.index_;
    }
    
    bool operator<=(const MatrixIterator& other) const {
        return index_ <= other.index_;
    }
    
    bool operator>(const MatrixIterator& other) const {
        return index_ > other.index_;
    }
    
    bool operator>=(const MatrixIterator& other) const {
        return index_ >= other.index_;
    }
};

// Const matrix iterator implementation
template<typename T, size_t N>
class ConstMatrixIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
    
private:
    const Matrix<T, N>* matrix_;
    size_t index_;
    
public:
    ConstMatrixIterator(const Matrix<T, N>* matrix, size_t index) 
        : matrix_(matrix), index_(index) {}
    
    reference operator*() const {
        return (*matrix_)[index_];
    }
    
    pointer operator->() const {
        return &(*matrix_)[index_];
    }
    
    ConstMatrixIterator& operator++() {
        ++index_;
        return *this;
    }
    
    ConstMatrixIterator operator++(int) {
        ConstMatrixIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    ConstMatrixIterator& operator--() {
        --index_;
        return *this;
    }
    
    ConstMatrixIterator operator--(int) {
        ConstMatrixIterator temp = *this;
        --(*this);
        return temp;
    }
    
    ConstMatrixIterator& operator+=(difference_type n) {
        index_ += n;
        return *this;
    }
    
    ConstMatrixIterator& operator-=(difference_type n) {
        index_ -= n;
        return *this;
    }
    
    ConstMatrixIterator operator+(difference_type n) const {
        return ConstMatrixIterator(matrix_, index_ + n);
    }
    
    ConstMatrixIterator operator-(difference_type n) const {
        return ConstMatrixIterator(matrix_, index_ - n);
    }
    
    difference_type operator-(const ConstMatrixIterator& other) const {
        return index_ - other.index_;
    }
    
    reference operator[](difference_type n) const {
        return (*matrix_)[index_ + n];
    }
    
    bool operator==(const ConstMatrixIterator& other) const {
        return matrix_ == other.matrix_ && index_ == other.index_;
    }
    
    bool operator!=(const ConstMatrixIterator& other) const {
        return !(*this == other);
    }
    
    bool operator<(const ConstMatrixIterator& other) const {
        return index_ < other.index_;
    }
    
    bool operator<=(const ConstMatrixIterator& other) const {
        return index_ <= other.index_;
    }
    
    bool operator>(const ConstMatrixIterator& other) const {
        return index_ > other.index_;
    }
    
    bool operator>=(const ConstMatrixIterator& other) const {
        return index_ >= other.index_;
    }
};

// Matrix implementation
template<typename T, size_t N>
class Matrix {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = MatrixIterator<T, N>;
    using const_iterator = ConstMatrixIterator<T, N>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
private:
    std::vector<T> data_;
    std::array<size_t, N> dimensions_;
    
    size_t calculate_index(const std::array<size_t, N>& indices) const {
        size_t index = 0;
        size_t multiplier = 1;
        
        for (size_t i = 0; i < N; ++i) {
            index += indices[i] * multiplier;
            multiplier *= dimensions_[i];
        }
        
        return index;
    }
    
    void validate_indices(const std::array<size_t, N>& indices) const {
        for (size_t i = 0; i < N; ++i) {
            if (indices[i] >= dimensions_[i]) {
                throw std::out_of_range("Matrix index out of range");
            }
        }
    }
    
public:
    // Constructors
    Matrix() : dimensions_{} {
        data_.resize(0);
    }
    
    explicit Matrix(const std::array<size_t, N>& dims) : dimensions_(dims) {
        size_t total_size = std::accumulate(dims.begin(), dims.end(), size_t(1), std::multiplies<size_t>());
        data_.resize(total_size);
    }
    
    Matrix(const std::array<size_t, N>& dims, const T& value) : dimensions_(dims) {
        size_t total_size = std::accumulate(dims.begin(), dims.end(), size_t(1), std::multiplies<size_t>());
        data_.resize(total_size, value);
    }
    
    Matrix(std::initializer_list<T> init) {
        if (N == 1) {
            dimensions_[0] = init.size();
            data_ = std::vector<T>(init);
        } else {
            throw std::invalid_argument("Initializer list constructor only supported for 1D matrices");
        }
    }
    
    // Copy constructor
    Matrix(const Matrix& other) : data_(other.data_), dimensions_(other.dimensions_) {}
    
    // Move constructor
    Matrix(Matrix&& other) noexcept 
        : data_(std::move(other.data_)), dimensions_(std::move(other.dimensions_)) {}
    
    // Destructor
    ~Matrix() = default;
    
    // Assignment operators
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data_ = other.data_;
            dimensions_ = other.dimensions_;
        }
        return *this;
    }
    
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            dimensions_ = std::move(other.dimensions_);
        }
        return *this;
    }
    
    // Element access
    T& operator[](size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= data_.size()) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data_[index];
    }
    
    T& operator()(const std::array<size_t, N>& indices) {
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    const T& operator()(const std::array<size_t, N>& indices) const {
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    // For 2D matrices
    template<typename U = T>
    typename std::enable_if<N == 2, U&>::type
    operator()(size_t row, size_t col) {
        std::array<size_t, 2> indices = {row, col};
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    template<typename U = T>
    typename std::enable_if<N == 2, const U&>::type
    operator()(size_t row, size_t col) const {
        std::array<size_t, 2> indices = {row, col};
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    // For 3D matrices
    template<typename U = T>
    typename std::enable_if<N == 3, U&>::type
    operator()(size_t x, size_t y, size_t z) {
        std::array<size_t, 3> indices = {x, y, z};
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    template<typename U = T>
    typename std::enable_if<N == 3, const U&>::type
    operator()(size_t x, size_t y, size_t z) const {
        std::array<size_t, 3> indices = {x, y, z};
        validate_indices(indices);
        return data_[calculate_index(indices)];
    }
    
    // Iterators
    iterator begin() {
        return iterator(this, 0);
    }
    
    const_iterator begin() const {
        return const_iterator(this, 0);
    }
    
    iterator end() {
        return iterator(this, data_.size());
    }
    
    const_iterator end() const {
        return const_iterator(this, data_.size());
    }
    
    const_iterator cbegin() const {
        return const_iterator(this, 0);
    }
    
    const_iterator cend() const {
        return const_iterator(this, data_.size());
    }
    
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
    
    // Capacity
    bool empty() const {
        return data_.empty();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    size_t dimension(size_t dim) const {
        if (dim >= N) {
            throw std::out_of_range("Dimension index out of range");
        }
        return dimensions_[dim];
    }
    
    const std::array<size_t, N>& dimensions() const {
        return dimensions_;
    }
    
    // Modifiers
    void resize(const std::array<size_t, N>& dims) {
        dimensions_ = dims;
        size_t total_size = std::accumulate(dims.begin(), dims.end(), size_t(1), std::multiplies<size_t>());
        data_.resize(total_size);
    }
    
    void resize(const std::array<size_t, N>& dims, const T& value) {
        dimensions_ = dims;
        size_t total_size = std::accumulate(dims.begin(), dims.end(), size_t(1), std::multiplies<size_t>());
        data_.resize(total_size, value);
    }
    
    void fill(const T& value) {
        std::fill(data_.begin(), data_.end(), value);
    }
    
    void swap(Matrix& other) noexcept {
        data_.swap(other.data_);
        dimensions_.swap(other.dimensions_);
    }
    
    // Arithmetic operators
    Matrix& operator+=(const Matrix& other) {
        if (dimensions_ != other.dimensions_) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }
        
        std::transform(data_.begin(), data_.end(), other.data_.begin(), 
                      data_.begin(), std::plus<T>());
        return *this;
    }
    
    Matrix& operator-=(const Matrix& other) {
        if (dimensions_ != other.dimensions_) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction");
        }
        
        std::transform(data_.begin(), data_.end(), other.data_.begin(), 
                      data_.begin(), std::minus<T>());
        return *this;
    }
    
    Matrix& operator*=(const T& scalar) {
        std::transform(data_.begin(), data_.end(), data_.begin(), 
                      [&scalar](const T& value) { return value * scalar; });
        return *this;
    }
    
    Matrix& operator/=(const T& scalar) {
        if (scalar == T{}) {
            throw std::invalid_argument("Division by zero");
        }
        
        std::transform(data_.begin(), data_.end(), data_.begin(), 
                      [&scalar](const T& value) { return value / scalar; });
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Matrix& other) const {
        return dimensions_ == other.dimensions_ && data_ == other.data_;
    }
    
    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
    
    // Utility functions
    T sum() const {
        return std::accumulate(data_.begin(), data_.end(), T{});
    }
    
    T min() const {
        if (data_.empty()) {
            throw std::runtime_error("Cannot find minimum of empty matrix");
        }
        return *std::min_element(data_.begin(), data_.end());
    }
    
    T max() const {
        if (data_.empty()) {
            throw std::runtime_error("Cannot find maximum of empty matrix");
        }
        return *std::max_element(data_.begin(), data_.end());
    }
    
    double mean() const {
        if (data_.empty()) {
            throw std::runtime_error("Cannot find mean of empty matrix");
        }
        return static_cast<double>(sum()) / data_.size();
    }
    
    // Display function
    void display() const {
        if (N == 1) {
            std::cout << "[";
            for (size_t i = 0; i < data_.size(); ++i) {
                std::cout << data_[i];
                if (i < data_.size() - 1) std::cout << ", ";
            }
            std::cout << "]" << std::endl;
        } else if (N == 2) {
            for (size_t i = 0; i < dimensions_[0]; ++i) {
                std::cout << "[";
                for (size_t j = 0; j < dimensions_[1]; ++j) {
                    std::cout << (*this)(i, j);
                    if (j < dimensions_[1] - 1) std::cout << ", ";
                }
                std::cout << "]" << std::endl;
            }
        } else {
            std::cout << "Matrix dimensions: ";
            for (size_t i = 0; i < N; ++i) {
                std::cout << dimensions_[i];
                if (i < N - 1) std::cout << " x ";
            }
            std::cout << std::endl;
        }
    }
};

// Non-member functions
template<typename T, size_t N>
Matrix<T, N> operator+(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
    Matrix<T, N> result = lhs;
    result += rhs;
    return result;
}

template<typename T, size_t N>
Matrix<T, N> operator-(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
    Matrix<T, N> result = lhs;
    result -= rhs;
    return result;
}

template<typename T, size_t N>
Matrix<T, N> operator*(const Matrix<T, N>& matrix, const T& scalar) {
    Matrix<T, N> result = matrix;
    result *= scalar;
    return result;
}

template<typename T, size_t N>
Matrix<T, N> operator*(const T& scalar, const Matrix<T, N>& matrix) {
    return matrix * scalar;
}

template<typename T, size_t N>
Matrix<T, N> operator/(const Matrix<T, N>& matrix, const T& scalar) {
    Matrix<T, N> result = matrix;
    result /= scalar;
    return result;
}

// Stream operators
template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& matrix) {
    if (N == 1) {
        os << "[";
        for (size_t i = 0; i < matrix.size(); ++i) {
            os << matrix[i];
            if (i < matrix.size() - 1) os << ", ";
        }
        os << "]";
    } else if (N == 2) {
        for (size_t i = 0; i < matrix.dimension(0); ++i) {
            os << "[";
            for (size_t j = 0; j < matrix.dimension(1); ++j) {
                os << matrix(i, j);
                if (j < matrix.dimension(1) - 1) os << ", ";
            }
            os << "]";
            if (i < matrix.dimension(0) - 1) os << std::endl;
        }
    } else {
        os << "Matrix dimensions: ";
        for (size_t i = 0; i < N; ++i) {
            os << matrix.dimension(i);
            if (i < N - 1) os << " x ";
        }
    }
    return os;
}

// Type aliases for common matrix types
template<typename T>
using Vector = Matrix<T, 1>;

template<typename T>
using Matrix2D = Matrix<T, 2>;

template<typename T>
using Matrix3D = Matrix<T, 3>;

} // namespace matrix

#endif // MATRIX_H
