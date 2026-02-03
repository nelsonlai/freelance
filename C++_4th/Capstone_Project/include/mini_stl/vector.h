#ifndef MINI_STL_VECTOR_H
#define MINI_STL_VECTOR_H

#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

namespace mini_stl {

// Forward declarations
template<typename T>
class vector;

template<typename T>
class vector_iterator;

// Vector iterator implementation
template<typename T>
class vector_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
private:
    pointer ptr_;
    
public:
    // Constructors
    vector_iterator() : ptr_(nullptr) {}
    explicit vector_iterator(pointer ptr) : ptr_(ptr) {}
    
    // Copy constructor and assignment
    vector_iterator(const vector_iterator& other) : ptr_(other.ptr_) {}
    vector_iterator& operator=(const vector_iterator& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
        }
        return *this;
    }
    
    // Dereference operators
    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    reference operator[](difference_type n) const { return ptr_[n]; }
    
    // Increment/decrement operators
    vector_iterator& operator++() {
        ++ptr_;
        return *this;
    }
    
    vector_iterator operator++(int) {
        vector_iterator temp = *this;
        ++ptr_;
        return temp;
    }
    
    vector_iterator& operator--() {
        --ptr_;
        return *this;
    }
    
    vector_iterator operator--(int) {
        vector_iterator temp = *this;
        --ptr_;
        return temp;
    }
    
    // Arithmetic operators
    vector_iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }
    
    vector_iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }
    
    vector_iterator operator+(difference_type n) const {
        return vector_iterator(ptr_ + n);
    }
    
    vector_iterator operator-(difference_type n) const {
        return vector_iterator(ptr_ - n);
    }
    
    difference_type operator-(const vector_iterator& other) const {
        return ptr_ - other.ptr_;
    }
    
    // Comparison operators
    bool operator==(const vector_iterator& other) const {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const vector_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    
    bool operator<(const vector_iterator& other) const {
        return ptr_ < other.ptr_;
    }
    
    bool operator<=(const vector_iterator& other) const {
        return ptr_ <= other.ptr_;
    }
    
    bool operator>(const vector_iterator& other) const {
        return ptr_ > other.ptr_;
    }
    
    bool operator>=(const vector_iterator& other) const {
        return ptr_ >= other.ptr_;
    }
    
    // Friend functions
    friend vector_iterator operator+(difference_type n, const vector_iterator& it) {
        return vector_iterator(it.ptr_ + n);
    }
};

// Vector implementation
template<typename T>
class vector {
public:
    // Type aliases
    using value_type = T;
    using allocator_type = std::allocator<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = vector_iterator<T>;
    using const_iterator = vector_iterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
private:
    pointer data_;
    size_type size_;
    size_type capacity_;
    allocator_type allocator_;
    
    // Helper functions
    void reallocate(size_type new_capacity) {
        if (new_capacity < size_) {
            throw std::invalid_argument("New capacity cannot be less than current size");
        }
        
        pointer new_data = allocator_.allocate(new_capacity);
        
        try {
            std::uninitialized_move(data_, data_ + size_, new_data);
        } catch (...) {
            allocator_.deallocate(new_data, new_capacity);
            throw;
        }
        
        // Destroy old elements
        for (size_type i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        
        allocator_.deallocate(data_, capacity_);
        
        data_ = new_data;
        capacity_ = new_capacity;
    }
    
    void grow_if_needed() {
        if (size_ >= capacity_) {
            size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
    }
    
public:
    // Constructors
    vector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit vector(size_type count, const T& value = T()) 
        : data_(nullptr), size_(count), capacity_(count) {
        if (count > 0) {
            data_ = allocator_.allocate(count);
            try {
                std::uninitialized_fill(data_, data_ + count, value);
            } catch (...) {
                allocator_.deallocate(data_, count);
                throw;
            }
        }
    }
    
    template<typename InputIt>
    vector(InputIt first, InputIt last) 
        : data_(nullptr), size_(0), capacity_(0) {
        size_type count = std::distance(first, last);
        if (count > 0) {
            data_ = allocator_.allocate(count);
            capacity_ = count;
            try {
                std::uninitialized_copy(first, last, data_);
                size_ = count;
            } catch (...) {
                allocator_.deallocate(data_, count);
                throw;
            }
        }
    }
    
    vector(std::initializer_list<T> init) 
        : data_(nullptr), size_(init.size()), capacity_(init.size()) {
        if (size_ > 0) {
            data_ = allocator_.allocate(size_);
            try {
                std::uninitialized_copy(init.begin(), init.end(), data_);
            } catch (...) {
                allocator_.deallocate(data_, size_);
                throw;
            }
        }
    }
    
    // Copy constructor
    vector(const vector& other) 
        : data_(nullptr), size_(other.size_), capacity_(other.size_) {
        if (size_ > 0) {
            data_ = allocator_.allocate(size_);
            try {
                std::uninitialized_copy(other.data_, other.data_ + size_, data_);
            } catch (...) {
                allocator_.deallocate(data_, size_);
                throw;
            }
        }
    }
    
    // Move constructor
    vector(vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // Destructor
    ~vector() {
        if (data_) {
            for (size_type i = 0; i < size_; ++i) {
                data_[i].~T();
            }
            allocator_.deallocate(data_, capacity_);
        }
    }
    
    // Assignment operators
    vector& operator=(const vector& other) {
        if (this != &other) {
            vector temp(other);
            swap(temp);
        }
        return *this;
    }
    
    vector& operator=(vector&& other) noexcept {
        if (this != &other) {
            if (data_) {
                for (size_type i = 0; i < size_; ++i) {
                    data_[i].~T();
                }
                allocator_.deallocate(data_, capacity_);
            }
            
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    vector& operator=(std::initializer_list<T> init) {
        vector temp(init);
        swap(temp);
        return *this;
    }
    
    // Element access
    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("vector::at");
        }
        return data_[pos];
    }
    
    const_reference at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("vector::at");
        }
        return data_[pos];
    }
    
    reference operator[](size_type pos) {
        return data_[pos];
    }
    
    const_reference operator[](size_type pos) const {
        return data_[pos];
    }
    
    reference front() {
        return data_[0];
    }
    
    const_reference front() const {
        return data_[0];
    }
    
    reference back() {
        return data_[size_ - 1];
    }
    
    const_reference back() const {
        return data_[size_ - 1];
    }
    
    pointer data() noexcept {
        return data_;
    }
    
    const_pointer data() const noexcept {
        return data_;
    }
    
    // Iterators
    iterator begin() noexcept {
        return iterator(data_);
    }
    
    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }
    
    const_iterator cbegin() const noexcept {
        return const_iterator(data_);
    }
    
    iterator end() noexcept {
        return iterator(data_ + size_);
    }
    
    const_iterator end() const noexcept {
        return const_iterator(data_ + size_);
    }
    
    const_iterator cend() const noexcept {
        return const_iterator(data_ + size_);
    }
    
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }
    
    // Capacity
    bool empty() const noexcept {
        return size_ == 0;
    }
    
    size_type size() const noexcept {
        return size_;
    }
    
    size_type max_size() const noexcept {
        return allocator_.max_size();
    }
    
    void reserve(size_type new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }
    
    size_type capacity() const noexcept {
        return capacity_;
    }
    
    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }
    
    // Modifiers
    void clear() noexcept {
        for (size_type i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }
    
    iterator insert(const_iterator pos, const T& value) {
        size_type index = pos - cbegin();
        if (size_ >= capacity_) {
            grow_if_needed();
        }
        
        // Move elements to make space
        for (size_type i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        
        // Insert new element
        data_[index] = value;
        ++size_;
        
        return iterator(data_ + index);
    }
    
    iterator insert(const_iterator pos, T&& value) {
        size_type index = pos - cbegin();
        if (size_ >= capacity_) {
            grow_if_needed();
        }
        
        // Move elements to make space
        for (size_type i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        
        // Insert new element
        data_[index] = std::move(value);
        ++size_;
        
        return iterator(data_ + index);
    }
    
    iterator insert(const_iterator pos, size_type count, const T& value) {
        size_type index = pos - cbegin();
        
        // Ensure we have enough capacity
        while (size_ + count > capacity_) {
            grow_if_needed();
        }
        
        // Move elements to make space
        for (size_type i = size_ + count - 1; i >= index + count; --i) {
            data_[i] = std::move(data_[i - count]);
        }
        
        // Insert new elements
        for (size_type i = 0; i < count; ++i) {
            data_[index + i] = value;
        }
        
        size_ += count;
        return iterator(data_ + index);
    }
    
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type count = std::distance(first, last);
        size_type index = pos - cbegin();
        
        // Ensure we have enough capacity
        while (size_ + count > capacity_) {
            grow_if_needed();
        }
        
        // Move elements to make space
        for (size_type i = size_ + count - 1; i >= index + count; --i) {
            data_[i] = std::move(data_[i - count]);
        }
        
        // Insert new elements
        for (size_type i = 0; i < count; ++i) {
            data_[index + i] = *first++;
        }
        
        size_ += count;
        return iterator(data_ + index);
    }
    
    iterator erase(const_iterator pos) {
        size_type index = pos - cbegin();
        
        // Move elements to fill gap
        for (size_type i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        
        --size_;
        data_[size_].~T();
        
        return iterator(data_ + index);
    }
    
    iterator erase(const_iterator first, const_iterator last) {
        size_type start_index = first - cbegin();
        size_type end_index = last - cbegin();
        size_type count = end_index - start_index;
        
        // Move elements to fill gap
        for (size_type i = start_index; i < size_ - count; ++i) {
            data_[i] = std::move(data_[i + count]);
        }
        
        // Destroy removed elements
        for (size_type i = size_ - count; i < size_; ++i) {
            data_[i].~T();
        }
        
        size_ -= count;
        return iterator(data_ + start_index);
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            grow_if_needed();
        }
        data_[size_] = value;
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            grow_if_needed();
        }
        data_[size_] = std::move(value);
        ++size_;
    }
    
    void pop_back() {
        if (size_ > 0) {
            --size_;
            data_[size_].~T();
        }
    }
    
    void resize(size_type count, const T& value = T()) {
        if (count > size_) {
            if (count > capacity_) {
                reallocate(count);
            }
            for (size_type i = size_; i < count; ++i) {
                data_[i] = value;
            }
        } else if (count < size_) {
            for (size_type i = count; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = count;
    }
    
    void swap(vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(allocator_, other.allocator_);
    }
    
    // Comparison operators
    bool operator==(const vector& other) const {
        if (size_ != other.size_) return false;
        for (size_type i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }
    
    bool operator!=(const vector& other) const {
        return !(*this == other);
    }
    
    bool operator<(const vector& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }
    
    bool operator<=(const vector& other) const {
        return !(other < *this);
    }
    
    bool operator>(const vector& other) const {
        return other < *this;
    }
    
    bool operator>=(const vector& other) const {
        return !(*this < other);
    }
};

// Non-member functions
template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template<typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs == rhs;
}

template<typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs != rhs;
}

template<typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs < rhs;
}

template<typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs <= rhs;
}

template<typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs > rhs;
}

template<typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs >= rhs;
}

} // namespace mini_stl

#endif // MINI_STL_VECTOR_H
