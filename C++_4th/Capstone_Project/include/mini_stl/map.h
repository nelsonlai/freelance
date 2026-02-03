#ifndef MINI_STL_MAP_H
#define MINI_STL_MAP_H

#include <memory>
#include <functional>
#include <stdexcept>
#include <initializer_list>

namespace mini_stl {

// Forward declarations
template<typename Key, typename Value, typename Compare = std::less<Key>>
class map;

template<typename Key, typename Value, typename Compare>
class map_iterator;

// Map node for balanced binary search tree
template<typename Key, typename Value>
struct map_node {
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
    using mapped_type = Value;
    
    value_type data;
    std::unique_ptr<map_node> left;
    std::unique_ptr<map_node> right;
    map_node* parent;
    int height;
    
    map_node(const value_type& val) 
        : data(val), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    
    map_node(value_type&& val) 
        : data(std::move(val)), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    
    template<typename... Args>
    map_node(Args&&... args) 
        : data(std::forward<Args>(args)...), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

// Map iterator implementation
template<typename Key, typename Value, typename Compare>
class map_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<const Key, Value>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    using node_type = map_node<Key, Value>;
    
private:
    node_type* node_;
    const map<Key, Value, Compare>* container_;
    
    node_type* find_min(node_type* n) const {
        while (n && n->left) {
            n = n->left.get();
        }
        return n;
    }
    
    node_type* find_max(node_type* n) const {
        while (n && n->right) {
            n = n->right.get();
        }
        return n;
    }
    
    node_type* find_successor(node_type* n) const {
        if (n->right) {
            return find_min(n->right.get());
        }
        
        node_type* parent = n->parent;
        while (parent && n == parent->right.get()) {
            n = parent;
            parent = parent->parent;
        }
        return parent;
    }
    
    node_type* find_predecessor(node_type* n) const {
        if (n->left) {
            return find_max(n->left.get());
        }
        
        node_type* parent = n->parent;
        while (parent && n == parent->left.get()) {
            n = parent;
            parent = parent->parent;
        }
        return parent;
    }
    
public:
    map_iterator() : node_(nullptr), container_(nullptr) {}
    
    map_iterator(node_type* node, const map<Key, Value, Compare>* container) 
        : node_(node), container_(container) {}
    
    reference operator*() const {
        return node_->data;
    }
    
    pointer operator->() const {
        return &node_->data;
    }
    
    map_iterator& operator++() {
        node_ = find_successor(node_);
        return *this;
    }
    
    map_iterator operator++(int) {
        map_iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    map_iterator& operator--() {
        if (node_) {
            node_ = find_predecessor(node_);
        } else {
            // End iterator case
            node_ = container_->root_.get();
            while (node_ && node_->right) {
                node_ = node_->right.get();
            }
        }
        return *this;
    }
    
    map_iterator operator--(int) {
        map_iterator temp = *this;
        --(*this);
        return temp;
    }
    
    bool operator==(const map_iterator& other) const {
        return node_ == other.node_;
    }
    
    bool operator!=(const map_iterator& other) const {
        return !(*this == other);
    }
};

// Map implementation using AVL tree
template<typename Key, typename Value, typename Compare>
class map {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const Key, Value>;
    using key_compare = Compare;
    using allocator_type = std::allocator<value_type>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = map_iterator<Key, Value, Compare>;
    using const_iterator = map_iterator<Key, const Value, Compare>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
private:
    using node_type = map_node<Key, Value>;
    std::unique_ptr<node_type> root_;
    size_type size_;
    key_compare comp_;
    
    // AVL tree helper functions
    int height(node_type* node) const {
        return node ? node->height : 0;
    }
    
    int balance_factor(node_type* node) const {
        return node ? height(node->left.get()) - height(node->right.get()) : 0;
    }
    
    void update_height(node_type* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));
        }
    }
    
    std::unique_ptr<node_type> rotate_right(std::unique_ptr<node_type> node) {
        auto left = std::move(node->left);
        node->left = std::move(left->right);
        if (node->left) {
            node->left->parent = node.get();
        }
        left->right = std::move(node);
        left->right->parent = left.get();
        left->parent = nullptr;
        
        update_height(left->right.get());
        update_height(left.get());
        
        return left;
    }
    
    std::unique_ptr<node_type> rotate_left(std::unique_ptr<node_type> node) {
        auto right = std::move(node->right);
        node->right = std::move(right->left);
        if (node->right) {
            node->right->parent = node.get();
        }
        right->left = std::move(node);
        right->left->parent = right.get();
        right->parent = nullptr;
        
        update_height(right->left.get());
        update_height(right.get());
        
        return right;
    }
    
    std::unique_ptr<node_type> balance(std::unique_ptr<node_type> node) {
        update_height(node.get());
        
        int bf = balance_factor(node.get());
        
        // Left heavy
        if (bf > 1) {
            if (balance_factor(node->left.get()) < 0) {
                node->left = rotate_left(std::move(node->left));
                node->left->parent = node.get();
            }
            return rotate_right(std::move(node));
        }
        
        // Right heavy
        if (bf < -1) {
            if (balance_factor(node->right.get()) > 0) {
                node->right = rotate_right(std::move(node->right));
                node->right->parent = node.get();
            }
            return rotate_left(std::move(node));
        }
        
        return node;
    }
    
    std::unique_ptr<node_type> insert_node(std::unique_ptr<node_type> node, const value_type& val) {
        if (!node) {
            size_++;
            return std::make_unique<node_type>(val);
        }
        
        if (comp_(val.first, node->data.first)) {
            node->left = insert_node(std::move(node->left), val);
            if (node->left) {
                node->left->parent = node.get();
            }
        } else if (comp_(node->data.first, val.first)) {
            node->right = insert_node(std::move(node->right), val);
            if (node->right) {
                node->right->parent = node.get();
            }
        } else {
            // Key already exists, update value
            node->data.second = val.second;
            return node;
        }
        
        return balance(std::move(node));
    }
    
    std::unique_ptr<node_type> remove_node(std::unique_ptr<node_type> node, const key_type& key) {
        if (!node) {
            return nullptr;
        }
        
        if (comp_(key, node->data.first)) {
            node->left = remove_node(std::move(node->left), key);
            if (node->left) {
                node->left->parent = node.get();
            }
        } else if (comp_(node->data.first, key)) {
            node->right = remove_node(std::move(node->right), key);
            if (node->right) {
                node->right->parent = node.get();
            }
        } else {
            // Found the node to remove
            if (!node->left || !node->right) {
                auto temp = std::move(node->left ? node->left : node->right);
                if (temp) {
                    temp->parent = node->parent;
                }
                size_--;
                return temp;
            }
            
            // Node has two children
            auto successor = find_min(node->right.get());
            node->data = successor->data;
            node->right = remove_node(std::move(node->right), successor->data.first);
            if (node->right) {
                node->right->parent = node.get();
            }
        }
        
        return balance(std::move(node));
    }
    
    node_type* find_min(node_type* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }
    
    node_type* find_max(node_type* node) const {
        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }
    
    node_type* find_node(node_type* node, const key_type& key) const {
        while (node) {
            if (comp_(key, node->data.first)) {
                node = node->left.get();
            } else if (comp_(node->data.first, key)) {
                node = node->right.get();
            } else {
                return node;
            }
        }
        return nullptr;
    }
    
public:
    // Constructors
    map() : root_(nullptr), size_(0), comp_() {}
    
    explicit map(const key_compare& comp) : root_(nullptr), size_(0), comp_(comp) {}
    
    map(std::initializer_list<value_type> init) : root_(nullptr), size_(0), comp_() {
        for (const auto& val : init) {
            insert(val);
        }
    }
    
    // Copy constructor
    map(const map& other) : root_(nullptr), size_(0), comp_(other.comp_) {
        for (const auto& val : other) {
            insert(val);
        }
    }
    
    // Move constructor
    map(map&& other) noexcept 
        : root_(std::move(other.root_)), size_(other.size_), comp_(std::move(other.comp_)) {
        other.size_ = 0;
    }
    
    // Destructor
    ~map() = default;
    
    // Assignment operators
    map& operator=(const map& other) {
        if (this != &other) {
            map temp(other);
            swap(temp);
        }
        return *this;
    }
    
    map& operator=(map&& other) noexcept {
        if (this != &other) {
            root_ = std::move(other.root_);
            size_ = other.size_;
            comp_ = std::move(other.comp_);
            other.size_ = 0;
        }
        return *this;
    }
    
    map& operator=(std::initializer_list<value_type> init) {
        map temp(init);
        swap(temp);
        return *this;
    }
    
    // Iterators
    iterator begin() {
        return iterator(find_min(root_.get()), this);
    }
    
    const_iterator begin() const {
        return const_iterator(find_min(root_.get()), this);
    }
    
    const_iterator cbegin() const {
        return const_iterator(find_min(root_.get()), this);
    }
    
    iterator end() {
        return iterator(nullptr, this);
    }
    
    const_iterator end() const {
        return const_iterator(nullptr, this);
    }
    
    const_iterator cend() const {
        return const_iterator(nullptr, this);
    }
    
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
    
    const_reverse_iterator crend() const {
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
        return std::numeric_limits<size_type>::max();
    }
    
    // Element access
    mapped_type& operator[](const key_type& key) {
        auto it = find(key);
        if (it != end()) {
            return it->second;
        }
        return insert({key, mapped_type{}}).first->second;
    }
    
    mapped_type& operator[](key_type&& key) {
        auto it = find(key);
        if (it != end()) {
            return it->second;
        }
        return insert({std::move(key), mapped_type{}}).first->second;
    }
    
    mapped_type& at(const key_type& key) {
        auto it = find(key);
        if (it != end()) {
            return it->second;
        }
        throw std::out_of_range("map::at");
    }
    
    const mapped_type& at(const key_type& key) const {
        auto it = find(key);
        if (it != end()) {
            return it->second;
        }
        throw std::out_of_range("map::at");
    }
    
    // Modifiers
    std::pair<iterator, bool> insert(const value_type& value) {
        size_type old_size = size_;
        root_ = insert_node(std::move(root_), value);
        if (root_) {
            root_->parent = nullptr;
        }
        
        auto it = find(value.first);
        bool inserted = (size_ > old_size);
        return {it, inserted};
    }
    
    std::pair<iterator, bool> insert(value_type&& value) {
        size_type old_size = size_;
        root_ = insert_node(std::move(root_), std::move(value));
        if (root_) {
            root_->parent = nullptr;
        }
        
        auto it = find(value.first);
        bool inserted = (size_ > old_size);
        return {it, inserted};
    }
    
    template<typename P>
    std::pair<iterator, bool> insert(P&& value) {
        return insert(value_type{std::forward<P>(value)});
    }
    
    iterator insert(const_iterator hint, const value_type& value) {
        // For simplicity, ignore hint
        return insert(value).first;
    }
    
    iterator insert(const_iterator hint, value_type&& value) {
        // For simplicity, ignore hint
        return insert(std::move(value)).first;
    }
    
    template<typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (auto it = first; it != last; ++it) {
            insert(*it);
        }
    }
    
    void insert(std::initializer_list<value_type> ilist) {
        for (const auto& val : ilist) {
            insert(val);
        }
    }
    
    iterator erase(const_iterator pos) {
        key_type key = pos->first;
        root_ = remove_node(std::move(root_), key);
        if (root_) {
            root_->parent = nullptr;
        }
        return find(key);
    }
    
    iterator erase(const_iterator first, const_iterator last) {
        iterator result = end();
        for (auto it = first; it != last; ++it) {
            result = erase(it);
        }
        return result;
    }
    
    size_type erase(const key_type& key) {
        size_type old_size = size_;
        root_ = remove_node(std::move(root_), key);
        if (root_) {
            root_->parent = nullptr;
        }
        return old_size - size_;
    }
    
    void swap(map& other) noexcept {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
        std::swap(comp_, other.comp_);
    }
    
    void clear() noexcept {
        root_.reset();
        size_ = 0;
    }
    
    // Lookup
    iterator find(const key_type& key) {
        return iterator(find_node(root_.get(), key), this);
    }
    
    const_iterator find(const key_type& key) const {
        return const_iterator(find_node(root_.get(), key), this);
    }
    
    size_type count(const key_type& key) const {
        return find(key) != end() ? 1 : 0;
    }
    
    iterator lower_bound(const key_type& key) {
        auto it = begin();
        while (it != end() && comp_(it->first, key)) {
            ++it;
        }
        return it;
    }
    
    const_iterator lower_bound(const key_type& key) const {
        auto it = begin();
        while (it != end() && comp_(it->first, key)) {
            ++it;
        }
        return it;
    }
    
    iterator upper_bound(const key_type& key) {
        auto it = begin();
        while (it != end() && !comp_(key, it->first)) {
            ++it;
        }
        return it;
    }
    
    const_iterator upper_bound(const key_type& key) const {
        auto it = begin();
        while (it != end() && !comp_(key, it->first)) {
            ++it;
        }
        return it;
    }
    
    std::pair<iterator, iterator> equal_range(const key_type& key) {
        return {lower_bound(key), upper_bound(key)};
    }
    
    std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
        return {lower_bound(key), upper_bound(key)};
    }
    
    // Observers
    key_compare key_comp() const {
        return comp_;
    }
    
    // Comparison operators
    bool operator==(const map& other) const {
        if (size() != other.size()) {
            return false;
        }
        return std::equal(begin(), end(), other.begin());
    }
    
    bool operator!=(const map& other) const {
        return !(*this == other);
    }
    
    bool operator<(const map& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }
    
    bool operator<=(const map& other) const {
        return !(other < *this);
    }
    
    bool operator>(const map& other) const {
        return other < *this;
    }
    
    bool operator>=(const map& other) const {
        return !(*this < other);
    }
};

// Non-member functions
template<typename Key, typename Value, typename Compare>
void swap(map<Key, Value, Compare>& lhs, map<Key, Value, Compare>& rhs) noexcept {
    lhs.swap(rhs);
}

} // namespace mini_stl

#endif // MINI_STL_MAP_H
