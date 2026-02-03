/*
 * Lesson 14.3: Advanced STL Iterators
 * 
 * This file demonstrates advanced STL iterators, iterator adapters,
 * custom iterators, and iterator concepts.
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

// Example 1: Iterator Adapters
namespace IteratorAdapters {
    
    // Reverse iterator adapter
    template<typename Iterator>
    class reverse_iterator_adapter {
    private:
        Iterator base_;
        
    public:
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using reference = typename std::iterator_traits<Iterator>::reference;
        
        reverse_iterator_adapter(Iterator base) : base_(base) {}
        
        reference operator*() const {
            Iterator temp = base_;
            return *--temp;
        }
        
        pointer operator->() const {
            Iterator temp = base_;
            return &*--temp;
        }
        
        reverse_iterator_adapter& operator++() {
            --base_;
            return *this;
        }
        
        reverse_iterator_adapter operator++(int) {
            reverse_iterator_adapter temp = *this;
            --base_;
            return temp;
        }
        
        reverse_iterator_adapter& operator--() {
            ++base_;
            return *this;
        }
        
        reverse_iterator_adapter operator--(int) {
            reverse_iterator_adapter temp = *this;
            ++base_;
            return temp;
        }
        
        bool operator==(const reverse_iterator_adapter& other) const {
            return base_ == other.base_;
        }
        
        bool operator!=(const reverse_iterator_adapter& other) const {
            return base_ != other.base_;
        }
        
        Iterator base() const { return base_; }
    };
    
    // Insert iterator adapter
    template<typename Container>
    class insert_iterator_adapter {
    private:
        Container* container_;
        typename Container::iterator position_;
        
    public:
        using iterator_category = std::output_iterator_tag;
        using value_type = typename Container::value_type;
        using difference_type = void;
        using pointer = void;
        using reference = void;
        
        insert_iterator_adapter(Container& container, typename Container::iterator pos)
            : container_(&container), position_(pos) {}
        
        insert_iterator_adapter& operator=(const value_type& value) {
            position_ = container_->insert(position_, value);
            ++position_;
            return *this;
        }
        
        insert_iterator_adapter& operator*() { return *this; }
        insert_iterator_adapter& operator++() { return *this; }
        insert_iterator_adapter& operator++(int) { return *this; }
    };
    
    // Transform iterator adapter
    template<typename Iterator, typename UnaryOp>
    class transform_iterator_adapter {
    private:
        Iterator base_;
        UnaryOp op_;
        
    public:
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        using value_type = typename std::result_of<UnaryOp(typename std::iterator_traits<Iterator>::reference)>::type;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using pointer = value_type*;
        using reference = value_type;
        
        transform_iterator_adapter(Iterator base, UnaryOp op) : base_(base), op_(op) {}
        
        reference operator*() const {
            return op_(*base_);
        }
        
        transform_iterator_adapter& operator++() {
            ++base_;
            return *this;
        }
        
        transform_iterator_adapter operator++(int) {
            transform_iterator_adapter temp = *this;
            ++base_;
            return temp;
        }
        
        bool operator==(const transform_iterator_adapter& other) const {
            return base_ == other.base_;
        }
        
        bool operator!=(const transform_iterator_adapter& other) const {
            return base_ != other.base_;
        }
    };
    
    // Filter iterator adapter
    template<typename Iterator, typename Predicate>
    class filter_iterator_adapter {
    private:
        Iterator base_;
        Iterator end_;
        Predicate pred_;
        
        void advance_to_valid() {
            while (base_ != end_ && !pred_(*base_)) {
                ++base_;
            }
        }
        
    public:
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using reference = typename std::iterator_traits<Iterator>::reference;
        
        filter_iterator_adapter(Iterator base, Iterator end, Predicate pred)
            : base_(base), end_(end), pred_(pred) {
            advance_to_valid();
        }
        
        reference operator*() const {
            return *base_;
        }
        
        pointer operator->() const {
            return &*base_;
        }
        
        filter_iterator_adapter& operator++() {
            ++base_;
            advance_to_valid();
            return *this;
        }
        
        filter_iterator_adapter operator++(int) {
            filter_iterator_adapter temp = *this;
            ++base_;
            advance_to_valid();
            return temp;
        }
        
        bool operator==(const filter_iterator_adapter& other) const {
            return base_ == other.base_;
        }
        
        bool operator!=(const filter_iterator_adapter& other) const {
            return base_ != other.base_;
        }
    };
    
    void demonstrateIteratorAdapters() {
        std::cout << "=== Iterator Adapters ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Reverse iterator
        std::cout << "Reverse iteration: ";
        for (auto it = reverse_iterator_adapter(vec.end()); it != reverse_iterator_adapter(vec.begin()); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Transform iterator
        auto square = [](int x) { return x * x; };
        std::cout << "Transform iteration (squares): ";
        for (auto it = transform_iterator_adapter(vec.begin(), square); 
             it != transform_iterator_adapter(vec.end(), square); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Filter iterator
        auto is_even = [](int x) { return x % 2 == 0; };
        std::cout << "Filter iteration (even numbers): ";
        for (auto it = filter_iterator_adapter(vec.begin(), vec.end(), is_even); 
             it != filter_iterator_adapter(vec.end(), vec.end(), is_even); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Insert iterator
        std::vector<int> result;
        auto insert_it = insert_iterator_adapter(result, result.end());
        std::copy(vec.begin(), vec.end(), insert_it);
        std::cout << "Insert iterator result: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 2: Custom Iterators
namespace CustomIterators {
    
    // Range iterator
    template<typename T>
    class range_iterator {
    private:
        T current_;
        T end_;
        T step_;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
        
        range_iterator(T current, T end, T step = 1) : current_(current), end_(end), step_(step) {}
        
        reference operator*() { return current_; }
        const reference operator*() const { return current_; }
        
        range_iterator& operator++() {
            current_ += step_;
            return *this;
        }
        
        range_iterator operator++(int) {
            range_iterator temp = *this;
            current_ += step_;
            return temp;
        }
        
        bool operator==(const range_iterator& other) const {
            return current_ >= end_ && other.current_ >= other.end_;
        }
        
        bool operator!=(const range_iterator& other) const {
            return !(*this == other);
        }
    };
    
    // Range class
    template<typename T>
    class range {
    private:
        T start_;
        T end_;
        T step_;
        
    public:
        range(T start, T end, T step = 1) : start_(start), end_(end), step_(step) {}
        
        range_iterator<T> begin() const { return range_iterator<T>(start_, end_, step_); }
        range_iterator<T> end() const { return range_iterator<T>(end_, end_, step_); }
    };
    
    // Matrix iterator
    template<typename T>
    class matrix_iterator {
    private:
        T* data_;
        size_t rows_;
        size_t cols_;
        size_t current_row_;
        size_t current_col_;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        matrix_iterator(T* data, size_t rows, size_t cols, size_t row = 0, size_t col = 0)
            : data_(data), rows_(rows), cols_(cols), current_row_(row), current_col_(col) {}
        
        reference operator*() { return data_[current_row_ * cols_ + current_col_]; }
        const reference operator*() const { return data_[current_row_ * cols_ + current_col_]; }
        
        pointer operator->() { return &data_[current_row_ * cols_ + current_col_]; }
        const pointer operator->() const { return &data_[current_row_ * cols_ + current_col_]; }
        
        matrix_iterator& operator++() {
            ++current_col_;
            if (current_col_ >= cols_) {
                current_col_ = 0;
                ++current_row_;
            }
            return *this;
        }
        
        matrix_iterator operator++(int) {
            matrix_iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        matrix_iterator& operator--() {
            if (current_col_ == 0) {
                current_col_ = cols_ - 1;
                --current_row_;
            } else {
                --current_col_;
            }
            return *this;
        }
        
        matrix_iterator operator--(int) {
            matrix_iterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const matrix_iterator& other) const {
            return current_row_ == other.current_row_ && current_col_ == other.current_col_;
        }
        
        bool operator!=(const matrix_iterator& other) const {
            return !(*this == other);
        }
        
        size_t row() const { return current_row_; }
        size_t col() const { return current_col_; }
    };
    
    // Matrix class
    template<typename T>
    class matrix {
    private:
        std::vector<T> data_;
        size_t rows_;
        size_t cols_;
        
    public:
        matrix(size_t rows, size_t cols) : data_(rows * cols), rows_(rows), cols_(cols) {}
        
        T& operator()(size_t row, size_t col) { return data_[row * cols_ + col]; }
        const T& operator()(size_t row, size_t col) const { return data_[row * cols_ + col]; }
        
        matrix_iterator<T> begin() { return matrix_iterator<T>(data_.data(), rows_, cols_); }
        matrix_iterator<T> end() { return matrix_iterator<T>(data_.data(), rows_, cols_, rows_, 0); }
        
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }
    };
    
    // Tree iterator
    template<typename T>
    class tree_node {
    public:
        T data_;
        std::unique_ptr<tree_node> left_;
        std::unique_ptr<tree_node> right_;
        
        tree_node(T data) : data_(data) {}
    };
    
    template<typename T>
    class tree_iterator {
    private:
        tree_node<T>* current_;
        std::vector<tree_node<T>*> stack_;
        
        void push_left(tree_node<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        tree_iterator(tree_node<T>* root) : current_(nullptr) {
            if (root) {
                push_left(root);
                if (!stack_.empty()) {
                    current_ = stack_.back();
                    stack_.pop_back();
                }
            }
        }
        
        tree_iterator() : current_(nullptr) {}
        
        reference operator*() { return current_->data_; }
        const reference operator*() const { return current_->data_; }
        
        pointer operator->() { return &current_->data_; }
        const pointer operator->() const { return &current_->data_; }
        
        tree_iterator& operator++() {
            if (current_->right_) {
                push_left(current_->right_.get());
            }
            
            if (stack_.empty()) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
                stack_.pop_back();
            }
            
            return *this;
        }
        
        tree_iterator operator++(int) {
            tree_iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const tree_iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const tree_iterator& other) const {
            return current_ != other.current_;
        }
    };
    
    // Tree class
    template<typename T>
    class tree {
    private:
        std::unique_ptr<tree_node<T>> root_;
        
    public:
        void insert(T value) {
            if (!root_) {
                root_ = std::make_unique<tree_node<T>>(value);
                return;
            }
            
            tree_node<T>* current = root_.get();
            while (true) {
                if (value < current->data_) {
                    if (current->left_) {
                        current = current->left_.get();
                    } else {
                        current->left_ = std::make_unique<tree_node<T>>(value);
                        break;
                    }
                } else {
                    if (current->right_) {
                        current = current->right_.get();
                    } else {
                        current->right_ = std::make_unique<tree_node<T>>(value);
                        break;
                    }
                }
            }
        }
        
        tree_iterator<T> begin() { return tree_iterator<T>(root_.get()); }
        tree_iterator<T> end() { return tree_iterator<T>(); }
    };
    
    void demonstrateCustomIterators() {
        std::cout << "\n=== Custom Iterators ===" << std::endl;
        
        // Range iterator
        std::cout << "Range iterator (1 to 10, step 2): ";
        for (int i : range<int>(1, 11, 2)) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        
        // Matrix iterator
        matrix<int> mat(3, 4);
        int value = 1;
        for (auto& elem : mat) {
            elem = value++;
        }
        
        std::cout << "Matrix iterator: ";
        for (auto it = mat.begin(); it != mat.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Tree iterator
        tree<int> t;
        t.insert(5);
        t.insert(3);
        t.insert(7);
        t.insert(1);
        t.insert(4);
        t.insert(6);
        t.insert(8);
        
        std::cout << "Tree iterator (in-order): ";
        for (const auto& elem : t) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 3: Iterator Concepts
namespace IteratorConcepts {
    
    // Iterator category traits
    template<typename Iterator>
    struct iterator_category_traits {
        static constexpr bool is_input = std::is_same_v<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::input_iterator_tag>;
        
        static constexpr bool is_output = std::is_same_v<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::output_iterator_tag>;
        
        static constexpr bool is_forward = std::is_same_v<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::forward_iterator_tag>;
        
        static constexpr bool is_bidirectional = std::is_same_v<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::bidirectional_iterator_tag>;
        
        static constexpr bool is_random_access = std::is_same_v<
            typename std::iterator_traits<Iterator>::iterator_category,
            std::random_access_iterator_tag>;
    };
    
    // Iterator distance calculation
    template<typename Iterator>
    typename std::iterator_traits<Iterator>::difference_type
    iterator_distance(Iterator first, Iterator last) {
        if constexpr (iterator_category_traits<Iterator>::is_random_access) {
            return last - first;
        } else {
            typename std::iterator_traits<Iterator>::difference_type distance = 0;
            while (first != last) {
                ++first;
                ++distance;
            }
            return distance;
        }
    }
    
    // Iterator advance
    template<typename Iterator>
    void iterator_advance(Iterator& it, typename std::iterator_traits<Iterator>::difference_type n) {
        if constexpr (iterator_category_traits<Iterator>::is_random_access) {
            it += n;
        } else {
            if (n >= 0) {
                while (n--) ++it;
            } else {
                while (n++) --it;
            }
        }
    }
    
    // Iterator next
    template<typename Iterator>
    Iterator iterator_next(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
        iterator_advance(it, n);
        return it;
    }
    
    // Iterator prev
    template<typename Iterator>
    Iterator iterator_prev(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
        iterator_advance(it, -n);
        return it;
    }
    
    void demonstrateIteratorConcepts() {
        std::cout << "\n=== Iterator Concepts ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::list<int> lst(vec.begin(), vec.end());
        
        // Iterator category traits
        std::cout << "Vector iterator is random access: " << iterator_category_traits<std::vector<int>::iterator>::is_random_access << std::endl;
        std::cout << "List iterator is bidirectional: " << iterator_category_traits<std::list<int>::iterator>::is_bidirectional << std::endl;
        std::cout << "List iterator is random access: " << iterator_category_traits<std::list<int>::iterator>::is_random_access << std::endl;
        
        // Iterator distance
        auto vec_distance = iterator_distance(vec.begin(), vec.end());
        auto lst_distance = iterator_distance(lst.begin(), lst.end());
        std::cout << "Vector distance: " << vec_distance << std::endl;
        std::cout << "List distance: " << lst_distance << std::endl;
        
        // Iterator advance
        auto vec_it = vec.begin();
        iterator_advance(vec_it, 5);
        std::cout << "Vector iterator after advance(5): " << *vec_it << std::endl;
        
        auto lst_it = lst.begin();
        iterator_advance(lst_it, 5);
        std::cout << "List iterator after advance(5): " << *lst_it << std::endl;
        
        // Iterator next/prev
        auto vec_next = iterator_next(vec.begin(), 3);
        std::cout << "Vector iterator next(3): " << *vec_next << std::endl;
        
        auto vec_prev = iterator_prev(vec.end(), 3);
        std::cout << "Vector iterator prev(3): " << *vec_prev << std::endl;
    }
}

// Example 4: Iterator Utilities
namespace IteratorUtilities {
    
    // Iterator range
    template<typename Iterator>
    class iterator_range {
    private:
        Iterator begin_;
        Iterator end_;
        
    public:
        iterator_range(Iterator begin, Iterator end) : begin_(begin), end_(end) {}
        
        Iterator begin() const { return begin_; }
        Iterator end() const { return end_; }
        
        bool empty() const { return begin_ == end_; }
        size_t size() const { return std::distance(begin_, end_); }
    };
    
    // Iterator zip
    template<typename Iterator1, typename Iterator2>
    class zip_iterator {
    private:
        Iterator1 it1_;
        Iterator2 it2_;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<typename std::iterator_traits<Iterator1>::value_type,
                                   typename std::iterator_traits<Iterator2>::value_type>;
        using difference_type = typename std::iterator_traits<Iterator1>::difference_type;
        using pointer = value_type*;
        using reference = value_type;
        
        zip_iterator(Iterator1 it1, Iterator2 it2) : it1_(it1), it2_(it2) {}
        
        reference operator*() const {
            return {*it1_, *it2_};
        }
        
        zip_iterator& operator++() {
            ++it1_;
            ++it2_;
            return *this;
        }
        
        zip_iterator operator++(int) {
            zip_iterator temp = *this;
            ++it1_;
            ++it2_;
            return temp;
        }
        
        bool operator==(const zip_iterator& other) const {
            return it1_ == other.it1_ || it2_ == other.it2_;
        }
        
        bool operator!=(const zip_iterator& other) const {
            return !(*this == other);
        }
    };
    
    // Iterator enumerate
    template<typename Iterator>
    class enumerate_iterator {
    private:
        Iterator it_;
        size_t index_;
        
    public:
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        using value_type = std::pair<size_t, typename std::iterator_traits<Iterator>::value_type>;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using pointer = value_type*;
        using reference = value_type;
        
        enumerate_iterator(Iterator it, size_t index = 0) : it_(it), index_(index) {}
        
        reference operator*() const {
            return {index_, *it_};
        }
        
        enumerate_iterator& operator++() {
            ++it_;
            ++index_;
            return *this;
        }
        
        enumerate_iterator operator++(int) {
            enumerate_iterator temp = *this;
            ++it_;
            ++index_;
            return temp;
        }
        
        bool operator==(const enumerate_iterator& other) const {
            return it_ == other.it_;
        }
        
        bool operator!=(const enumerate_iterator& other) const {
            return it_ != other.it_;
        }
    };
    
    // Iterator chain
    template<typename Iterator1, typename Iterator2>
    class chain_iterator {
    private:
        Iterator1 it1_;
        Iterator1 end1_;
        Iterator2 it2_;
        Iterator2 end2_;
        bool in_first_;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = typename std::iterator_traits<Iterator1>::value_type;
        using difference_type = typename std::iterator_traits<Iterator1>::difference_type;
        using pointer = typename std::iterator_traits<Iterator1>::pointer;
        using reference = typename std::iterator_traits<Iterator1>::reference;
        
        chain_iterator(Iterator1 it1, Iterator1 end1, Iterator2 it2, Iterator2 end2)
            : it1_(it1), end1_(end1), it2_(it2), end2_(end2), in_first_(true) {}
        
        reference operator*() const {
            return in_first_ ? *it1_ : *it2_;
        }
        
        chain_iterator& operator++() {
            if (in_first_) {
                ++it1_;
                if (it1_ == end1_) {
                    in_first_ = false;
                }
            } else {
                ++it2_;
            }
            return *this;
        }
        
        chain_iterator operator++(int) {
            chain_iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const chain_iterator& other) const {
            return (in_first_ && it1_ == end1_ && other.in_first_ && other.it1_ == other.end1_) ||
                   (!in_first_ && it2_ == end2_ && !other.in_first_ && other.it2_ == other.end2_);
        }
        
        bool operator!=(const chain_iterator& other) const {
            return !(*this == other);
        }
    };
    
    void demonstrateIteratorUtilities() {
        std::cout << "\n=== Iterator Utilities ===" << std::endl;
        
        std::vector<int> vec1 = {1, 2, 3, 4, 5};
        std::vector<int> vec2 = {6, 7, 8, 9, 10};
        
        // Iterator range
        auto range = iterator_range(vec1.begin() + 1, vec1.end() - 1);
        std::cout << "Iterator range (1 to end-1): ";
        for (const auto& elem : range) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Zip iterator
        std::cout << "Zip iterator: ";
        for (auto it = zip_iterator(vec1.begin(), vec2.begin()); 
             it != zip_iterator(vec1.end(), vec2.end()); ++it) {
            std::cout << "{" << it->first << ", " << it->second << "} ";
        }
        std::cout << std::endl;
        
        // Enumerate iterator
        std::cout << "Enumerate iterator: ";
        for (auto it = enumerate_iterator(vec1.begin()); 
             it != enumerate_iterator(vec1.end()); ++it) {
            std::cout << "[" << it->first << "]=" << it->second << " ";
        }
        std::cout << std::endl;
        
        // Chain iterator
        std::cout << "Chain iterator: ";
        for (auto it = chain_iterator(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()); 
             it != chain_iterator(vec1.end(), vec1.end(), vec2.end(), vec2.end()); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

// Example 5: Iterator Performance
namespace IteratorPerformance {
    
    // Performance measurement for different iterator types
    template<typename Iterator>
    void measure_iterator_performance(Iterator first, Iterator last, const std::string& name) {
        const size_t iterations = 1000000;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < iterations; ++i) {
            for (auto it = first; it != last; ++it) {
                volatile auto value = *it;
                (void)value;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << name << " iteration time: " << duration.count() << " microseconds" << std::endl;
    }
    
    // Performance comparison for different containers
    void demonstrateIteratorPerformance() {
        std::cout << "\n=== Iterator Performance ===" << std::endl;
        
        const size_t size = 10000;
        
        // Vector
        std::vector<int> vec(size);
        std::iota(vec.begin(), vec.end(), 0);
        measure_iterator_performance(vec.begin(), vec.end(), "Vector");
        
        // List
        std::list<int> lst(vec.begin(), vec.end());
        measure_iterator_performance(lst.begin(), lst.end(), "List");
        
        // Deque
        std::deque<int> dq(vec.begin(), vec.end());
        measure_iterator_performance(dq.begin(), dq.end(), "Deque");
        
        // Set
        std::set<int> s(vec.begin(), vec.end());
        measure_iterator_performance(s.begin(), s.end(), "Set");
        
        // Unordered set
        std::unordered_set<int> us(vec.begin(), vec.end());
        measure_iterator_performance(us.begin(), us.end(), "Unordered Set");
        
        // Array
        std::array<int, 10000> arr;
        std::iota(arr.begin(), arr.end(), 0);
        measure_iterator_performance(arr.begin(), arr.end(), "Array");
        
        // Performance comparison
        std::cout << "\nPerformance comparison (relative to vector):" << std::endl;
        std::cout << "Vector: 1.0x (baseline)" << std::endl;
        std::cout << "Array: ~1.0x (similar to vector)" << std::endl;
        std::cout << "Deque: ~1.1x (slightly slower)" << std::endl;
        std::cout << "List: ~2.0x (much slower due to pointer chasing)" << std::endl;
        std::cout << "Set: ~1.5x (tree traversal overhead)" << std::endl;
        std::cout << "Unordered Set: ~1.2x (hash table iteration)" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced STL Iterators Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced STL iterators, iterator adapters,\n"
              << "custom iterators, and iterator concepts.\n" << std::endl;
    
    // Demonstrate various advanced iterator concepts
    IteratorAdapters::demonstrateIteratorAdapters();
    CustomIterators::demonstrateCustomIterators();
    IteratorConcepts::demonstrateIteratorConcepts();
    IteratorUtilities::demonstrateIteratorUtilities();
    IteratorPerformance::demonstrateIteratorPerformance();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Iterator adapters extend the functionality of existing iterators" << std::endl;
    std::cout << "2. Custom iterators can be created for specialized data structures" << std::endl;
    std::cout << "3. Iterator concepts define the capabilities and requirements of iterators" << std::endl;
    std::cout << "4. Iterator utilities provide convenient operations and combinations" << std::endl;
    std::cout << "5. Iterator performance varies significantly between different container types" << std::endl;
    std::cout << "6. Iterator categories determine the operations available and performance characteristics" << std::endl;
    std::cout << "7. Custom iterators enable seamless integration with STL algorithms" << std::endl;
    std::cout << "8. Iterator adapters can be composed to create powerful iteration patterns" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o advanced_stl_iterators 03_Advanced_STL_Iterators.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o advanced_stl_iterators 03_Advanced_STL_Iterators.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Advanced_STL_Iterators.cpp
 * 
 * Running:
 * ./advanced_stl_iterators (Linux/macOS)
 * advanced_stl_iterators.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best iterator support.
 * 
 * Advanced STL Iterators Notes:
 * - Iterator adapters extend the functionality of existing iterators
 * - Custom iterators can be created for specialized data structures
 * - Iterator concepts define the capabilities and requirements of iterators
 * - Iterator utilities provide convenient operations and combinations
 * - Iterator performance varies significantly between different container types
 * - Iterator categories determine the operations available and performance characteristics
 * - Custom iterators enable seamless integration with STL algorithms
 * - Iterator adapters can be composed to create powerful iteration patterns
 */"""
