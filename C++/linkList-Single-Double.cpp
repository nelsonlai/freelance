/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap
#include <memory>   // std::unique_ptr

// lists_int.cpp
// A teaching/demo implementation of two list types storing `int`:
//  - SinglyLinkedListInt: simple singly-linked list with head/tail pointers
//  - DoublyLinkedListInt: doubly-linked list implemented with sentinel nodes
//
// Build (from project root):
//   g++ -std=c++17 -O2 -Wall -Wextra -pedantic linkList-Single-Double.cpp && ./a.out
//
// The file is intentionally verbose and slightly lower-level (manual new/delete)
// so students can see ownership, pointer manipulation, and common list algorithms.
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef>  // std::size_t
#include <utility>  // std::swap

/* =========================================
 * SinglyLinkedListInt
 *  - Stores ints
 *  - O(1): push_front / push_back (amortized, using tail_)
 *  - O(n): insert / erase / find / index access
 * ========================================= */
// ----------------------------------------
// SinglyLinkedListInt
// - Stores ints in nodes linked via `next` pointers
// - Amortized O(1) push_back because we keep a `tail_` pointer
// - O(1) push_front and pop_front
// - O(n) insert/erase/find/index access
// This is intentionally minimal to focus on pointer logic rather than iterators.
class SinglyLinkedListInt {
private:
    struct Node {
        int   value;
        // `next` owns the remainder of the list. Using unique_ptr means we don't
        // need to manually delete nodes: destruction of head_ will recursively
        // free the list. prev/parent pointers (non-owning) would be raw pointers.
        std::unique_ptr<Node> next;
        // Node constructors: one for creating a node with an owning next pointer
        explicit Node(int v, std::unique_ptr<Node> n=nullptr) : value(v), next(std::move(n)) {}
    };

    // head_ now owns the first node via unique_ptr. tail_ is a non-owning
    // raw pointer to the last node (convenience for O(1) push_back).
    std::unique_ptr<Node> head_; // owning pointer to first node
    Node* tail_;                // non-owning pointer to last node (nullptr if empty)
    std::size_t size_;    // number of elements

public:
    // npos is used to indicate "not found" from find()
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    // --- lifecycle ---
    // Default constructor: empty list
    SinglyLinkedListInt() : head_(nullptr), tail_(nullptr), size_(0) {}

    // Deep copy: copies values from `other` into newly allocated nodes.
    // Complexity: O(n) where n = other.size().
    // Deep copy: we must duplicate nodes since ownership can't be shared.
    SinglyLinkedListInt(const SinglyLinkedListInt& other) : SinglyLinkedListInt() {
        for (Node* cur = other.head_.get(); cur; cur = cur->next.get()) push_back(cur->value);
    }

    // Move constructor: steal pointers from `other` and leave it in a valid empty state.
    // This is O(1).
    // Move: transfer ownership of head_ and copy tail_/size. Reset other.
    SinglyLinkedListInt(SinglyLinkedListInt&& other) noexcept
        : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
        other.tail_ = nullptr; other.size_ = 0;
    }

    // Copy-and-swap assignment for strong exception safety.
    // The parameter is taken by value to reuse copy/move constructors.
    SinglyLinkedListInt& operator=(SinglyLinkedListInt other) noexcept {
        swap(other); return *this;
    }

    // Destructor: free all nodes
    ~SinglyLinkedListInt() { clear(); }

    // Swap contents with another list. O(1).
    void swap(SinglyLinkedListInt& other) noexcept {
    head_.swap(other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
    }

    // --- basic info ---
    // Capacity queries
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }

    // Access first element. Throws if list is empty.
    int& front() {
        if (empty()) throw std::out_of_range("front() on empty list");
        return head_->value;
    }
    const int& front() const {
        if (empty()) throw std::out_of_range("front() on empty list");
        return head_->value;
    }
    // Access last element. Throws if list is empty.
    int& back() {
        if (empty()) throw std::out_of_range("back() on empty list");
        return tail_->value;
    }
    const int& back() const {
        if (empty()) throw std::out_of_range("back() on empty list");
        return tail_->value;
    }

    // --- modifiers ---
    // Clear the list by deleting every node. Leaves an empty list.
    // Complexity: O(n)
    // With unique_ptr ownership we can clear by resetting head_. tail_ must
    // be updated to nullptr and size_ set to 0.
    void clear() noexcept {
        head_.reset(); // recursively deletes nodes via unique_ptr chain
        tail_ = nullptr;
        size_ = 0;
    }

    // Insert at beginning. O(1).
    void push_front(int v) {
        // Create new node that takes ownership of current head_
        head_ = std::make_unique<Node>(v, std::move(head_));
        ++size_;
        if (!tail_) tail_ = head_.get();  // if list was empty, tail_ also points to new node
    }

    // Append to end. O(1).
    void push_back(int v) {
        auto node = std::make_unique<Node>(v);
        Node* node_raw = node.get();
        if (tail_) {
            // tail_->next is a unique_ptr, take ownership of the new node
            tail_->next = std::move(node);
            tail_ = node_raw;
        } else {
            // empty list: head_ takes ownership
            head_ = std::move(node);
            tail_ = head_.get();
        }
        ++size_;
    }

    // Remove first element. O(1).
    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front() on empty list");
        // release first node by moving head_->next into head_
        head_ = std::move(head_->next);
        if (!head_) tail_ = nullptr;  // list became empty
        --size_;
    }

    // Insert BEFORE position `index` (0..size). index==size -> push_back.
    // Insert BEFORE position `index` (0..size). index==size -> push_back.
    // Complexity: O(index) due to traversal from head.
    void insert(std::size_t index, int v) {
        if (index > size_) throw std::out_of_range("insert index out of range");
        if (index == 0) { push_front(v); return; }
        if (index == size_) { push_back(v); return; }

        // Walk to node just before the insertion location. We traverse using
        // raw pointers since ownership is handled by unique_ptr.
        Node* prev = head_.get();
        for (std::size_t i = 1; i < index; ++i) prev = prev->next.get();
        // Create new node that takes ownership of prev->next
        prev->next = std::make_unique<Node>(v, std::move(prev->next));
        ++size_;
    }

    // Erase element at `index` (0..size-1)
    // Erase element at `index` (0..size-1). O(index)
    void erase(std::size_t index) {
        if (index >= size_) throw std::out_of_range("erase index out of range");
        if (index == 0) { pop_front(); return; }

        // Walk to node just before the victim
        Node* prev = head_.get();
        for (std::size_t i = 1; i < index; ++i) prev = prev->next.get();
        // Move ownership of victim out, then move victim->next into prev->next
        std::unique_ptr<Node> victim = std::move(prev->next);
        prev->next = std::move(victim->next);
        if (!prev->next) tail_ = prev; // if we removed last element, update tail_
        --size_;
    }

    // Linear search; returns npos if not found
    // Linear search: return index of first matching element or npos if not found.
    // Complexity: O(n)
    std::size_t find(int key) const {
        std::size_t i = 0;
        for (Node* cur = head_.get(); cur; cur = cur->next.get(), ++i)
            if (cur->value == key) return i;
        return npos;
    }

    // Collect values into a std::vector for easy iteration/printing in demos.
    std::vector<int> to_vector() const {
        std::vector<int> out; out.reserve(size_);
        for (Node* cur = head_.get(); cur; cur = cur->next.get()) out.push_back(cur->value);
        return out;
    }

    // ------------------ Iterator support ------------------
    // Simple forward iterator that allows range-based for loops.
    struct iterator {
        Node* cur;
        using value_type = int;
        using reference = int&;
        using pointer = int*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator(Node* p = nullptr) : cur(p) {}
        int& operator*() const { return cur->value; }
        iterator& operator++() { cur = cur->next.get(); return *this; }
        iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }
        bool operator==(const iterator& o) const { return cur == o.cur; }
        bool operator!=(const iterator& o) const { return cur != o.cur; }
    };

    iterator begin() { return iterator(head_.get()); }
    iterator end()   { return iterator(nullptr); }
    // const iterators
    struct const_iterator {
        const Node* cur;
        using value_type = int;
        using reference = const int&;
        using pointer = const int*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        const_iterator(const Node* p = nullptr) : cur(p) {}
        const int& operator*() const { return cur->value; }
        const_iterator& operator++() { cur = cur->next.get(); return *this; }
        bool operator==(const const_iterator& o) const { return cur == o.cur; }
        bool operator!=(const const_iterator& o) const { return cur != o.cur; }
    };
    const_iterator begin() const { return const_iterator(head_.get()); }
    const_iterator end() const   { return const_iterator(nullptr); }
};


/* =========================================
 * DoublyLinkedListInt (with sentinels)
 *  - Two dummy nodes: head_ (before first) and tail_ (after last)
 *  - O(1): push_front / push_back / pop_front / pop_back
 *  - O(min(i, n-i)): insert / erase / index access
 * ========================================= */
// ----------------------------------------
// DoublyLinkedListInt (with sentinels)
// - Uses two dummy sentinel nodes `head_` and `tail_` to simplify edge cases
// - All of push_front/push_back/pop_front/pop_back are O(1)
// - Insert/erase/index access cost O(min(i, n-i)) by walking from the closer end
class DoublyLinkedListInt {
private:
    struct Node {
        int   value;   // for sentinels this is unused
        Node* prev;
        Node* next;
    // Default ctor builds an empty node (used for sentinels)
    Node()              : value(0), prev(nullptr), next(nullptr) {}  // sentinel ctor
    explicit Node(int v): value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_;        // sentinel before first element
    Node* tail_;        // sentinel after last element
    std::size_t size_;

    // Insert a new node with value between adjacent nodes left <-> right
    // Insert a new node with value between adjacent nodes left <-> right
    // Preconditions (caller responsibility): left->next == right && right->prev == left
    Node* insert_between(Node* left, Node* right, int val) {
        Node* n = new Node(val);
        n->prev = left; n->next = right;
        left->next = n;  right->prev = n;
        ++size_;
        return n;
    }

    // Remove `n` (a real node), return its value
    // Remove `n` (a real node), stitch neighbors together and return its value.
    // Caller must ensure `n` is not a sentinel.
    int unlink(Node* n) {
        Node* L = n->prev; Node* R = n->next;
        L->next = R; R->prev = L;
        int v = n->value;
        delete n;
        --size_;
        return v;
    }

    // Return node at index (0..size_-1); walk from closer end
    // Return node at index (0..size_-1); walk from closer end for efficiency.
    // This function is a key optimization: it avoids always walking from head.
    Node* node_at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("index out of range");
        if (index <= size_ / 2) {
            Node* cur = head_->next; // start after head sentinel
            for (std::size_t i = 0; i < index; ++i) cur = cur->next;
            return cur;
        } else {
            Node* cur = tail_->prev; // start before tail sentinel
            for (std::size_t i = size_-1; i > index; --i) cur = cur->prev;
            return cur;
        }
    }

public:
    // Construct empty list with two sentinels; simplifies push/pop edge cases.
    DoublyLinkedListInt() : head_(new Node()), tail_(new Node()), size_(0) {
        head_->next = tail_;
        tail_->prev = head_;
    }

    // Deep copy
    // Deep copy: iterate the other list and push_back each value.
    DoublyLinkedListInt(const DoublyLinkedListInt& other) : DoublyLinkedListInt() {
        for (Node* cur = other.head_->next; cur != other.tail_; cur = cur->next)
            push_back(cur->value);
    }

    // Move
    // Move constructor: steal internal sentinels and size, then reinitialize `other`
    // to a valid empty list so its destructor remains safe.
    DoublyLinkedListInt(DoublyLinkedListInt&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        // Re-init 'other' to a valid empty list
        other.head_ = new Node(); other.tail_ = new Node(); other.size_ = 0;
        other.head_->next = other.tail_;
        other.tail_->prev = other.head_;
    }

    // Copy-and-swap assignment
    DoublyLinkedListInt& operator=(DoublyLinkedListInt other) noexcept {
        swap(other); return *this;
    }

    // Destructor: clear all real nodes then delete sentinels.
    ~DoublyLinkedListInt() {
        clear();
        delete head_;
        delete tail_;
    }

    // Swap pointers and size. O(1).
    void swap(DoublyLinkedListInt& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    // --- basic info ---
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }

    // Access first real element (after head sentinel)
    int& front() {
        if (empty()) throw std::out_of_range("front() on empty list");
        return head_->next->value;
    }
    const int& front() const {
        if (empty()) throw std::out_of_range("front() on empty list");
        return head_->next->value;
    }

    // Access last real element (before tail sentinel)
    int& back() {
        if (empty()) throw std::out_of_range("back() on empty list");
        return tail_->prev->value;
    }
    const int& back() const {
        if (empty()) throw std::out_of_range("back() on empty list");
        return tail_->prev->value;
    }

    // --- modifiers (all O(1)) ---
    // All push/pop operations are implemented via insert_between / unlink
    // which centralize pointer updates and size accounting.
    void push_front(int v) { insert_between(head_, head_->next, v); }
    void push_back (int v) { insert_between(tail_->prev, tail_, v); }

    // Remove and return value from front/back. O(1).
    int pop_front() {
        if (empty()) throw std::out_of_range("pop_front() on empty list");
        return unlink(head_->next);
    }
    int pop_back() {
        if (empty()) throw std::out_of_range("pop_back() on empty list");
        return unlink(tail_->prev);
    }

    // Clear all real nodes but keep sentinels intact.
    void clear() noexcept {
        Node* cur = head_->next;
        while (cur != tail_) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_->next = tail_;
        tail_->prev = head_;
        size_ = 0;
    }

    // Insert BEFORE position `index` (0..size); index >= size -> push_back
    // Insert BEFORE position `index` (0..size); index >= size -> push_back
    // Uses node_at to find the insertion point efficiently.
    void insert(std::size_t index, int v) {
        if (index == 0) { push_front(v); return; }
        if (index >= size_) { push_back(v); return; }
        Node* right = node_at(index);
        insert_between(right->prev, right, v);
    }

    // Erase element at index. node_at does bounds checking and picks direction.
    void erase(std::size_t index) {
        Node* victim = node_at(index);
        unlink(victim);
    }

    std::vector<int> to_vector() const {
        std::vector<int> out; out.reserve(size_);
        for (Node* cur = head_->next; cur != tail_; cur = cur->next) out.push_back(cur->value);
        return out;
    }
};


/* ======================
 * Demo / sanity checks
 * ====================== */
// The demo shows basic usage and prints intermediate results. Students can
// step through these operations to see how the lists evolve.
// The demo is wrapped in a guard so tests can include this file without
// creating a duplicate `main` symbol. Define LINKED_LISTS_NO_MAIN to skip.
int main() {
    std::cout << "--- SinglyLinkedListInt demo ---\n";
    SinglyLinkedListInt s;
    // Sequence of operations demonstrating push_front/push_back/insert
    s.push_back(2); s.push_front(1); s.push_back(3); s.push_back(4);
    s.insert(2, 99);                   // [1, 2, 99, 3, 4]
    std::cout << "size=" << s.size()
              << " front=" << s.front()
              << " back="  << s.back() << "\n";
    // Print contents (uses to_vector for convenience)
    for (int x : s.to_vector()) std::cout << x << " "; std::cout << "\n";
    s.erase(2);                        // remove 99 -> [1,2,3,4]
    s.pop_front();                     // -> [2,3,4]
    for (int x : s.to_vector()) std::cout << x << " "; std::cout << "\n";

    std::cout << "\n--- DoublyLinkedListInt demo ---\n";
    DoublyLinkedListInt d;
    // Use a mix of push_front/push_back to show order invariants
    d.push_front(2); d.push_front(1); d.push_back(3); d.push_back(4); // 1 2 3 4
    d.insert(2, 42);                 // 1 2 42 3 4
    std::cout << "front=" << d.front()
              << " back="  << d.back()
              << " size="  << d.size() << "\n";
    for (int x : d.to_vector()) std::cout << x << " "; std::cout << "\n";
    d.erase(1);                       // remove 2 -> 1 42 3 4
    std::cout << "pop_back=" << d.pop_back() << "\n"; // removes 4
    for (int x : d.to_vector()) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}