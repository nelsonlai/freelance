/*
 * TREE DATA STRUCTURE EXAMPLES EXAMPLES
 * 
 * This file demonstrates tree data structure implementation and algorithms:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental TREE DATA STRUCTURE concepts
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

// AVL Tree (self-balancing binary search tree) - C++ translation
// Converted from a Python implementation; designed for teaching with
// extensive inline comments explaining behavior, invariants and complexity.
//
// Build/test: g++ -std=c++17 -O2 -Wall -Wextra tree_AVL.cpp -o tree_AVL

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Node for AVL tree. We use std::unique_ptr for child ownership so
// memory is automatically freed when nodes are replaced or the tree is
// destroyed. For simplicity `height` is stored on each node; leaves have
// height 1 (matching the Python version semantics).
struct AVLNode {
    int value;
    std::unique_ptr<AVLNode> left;
    std::unique_ptr<AVLNode> right;
    int height;
    AVLNode(int v) : value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    std::unique_ptr<AVLNode> root;

    AVLTree() : root(nullptr) {}

    // Utility: return height of node (0 for nullptr)
    static int height(const AVLNode* n) { return n ? n->height : 0; }

    // Balance factor: height(left) - height(right)
    static int balance_factor(const AVLNode* n) { return n ? height(n->left.get()) - height(n->right.get()) : 0; }

    // Update node height from children
    static void update_height(AVLNode* n) {
        if (n) n->height = 1 + std::max(height(n->left.get()), height(n->right.get()));
    }

    // Right rotation around y
    std::unique_ptr<AVLNode> right_rotate(std::unique_ptr<AVLNode> y) {
        // y must have a left child
        auto x = std::move(y->left);
        auto T2 = std::move(x->right);

        // Perform rotation
        x->right = std::move(y);
        x->right->left = std::move(T2);

        // Update heights
        update_height(x->right.get());
        update_height(x.get());

        return x;
    }

    // Left rotation around x
    std::unique_ptr<AVLNode> left_rotate(std::unique_ptr<AVLNode> x) {
        auto y = std::move(x->right);
        auto T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        update_height(y->left.get());
        update_height(y.get());

        return y;
    }

    // Insert value into subtree rooted at node, returning new subtree root
    std::unique_ptr<AVLNode> insert_node(std::unique_ptr<AVLNode> node, int value) {
        if (!node) return std::make_unique<AVLNode>(value);
        if (value < node->value) node->left = insert_node(std::move(node->left), value);
        else node->right = insert_node(std::move(node->right), value); // duplicates to right

        update_height(node.get());
        int bf = balance_factor(node.get());

        // LL
        if (bf > 1 && value < node->left->value) return right_rotate(std::move(node));
        // RR
        if (bf < -1 && value > node->right->value) return left_rotate(std::move(node));
        // LR
        if (bf > 1 && value > node->left->value) {
            node->left = left_rotate(std::move(node->left));
            return right_rotate(std::move(node));
        }
        // RL
        if (bf < -1 && value < node->right->value) {
            node->right = right_rotate(std::move(node->right));
            return left_rotate(std::move(node));
        }

        return node;
    }

    // Public insert wrapper
    void insert(int value) { root = insert_node(std::move(root), value); }

    // Find minimum node in subtree (by pointer) - used for deletion
    static AVLNode* min_node(AVLNode* node) {
        AVLNode* cur = node;
        while (cur && cur->left) cur = cur->left.get();
        return cur;
    }

    // Delete value from subtree
    std::unique_ptr<AVLNode> delete_node(std::unique_ptr<AVLNode> node, int value) {
        if (!node) return nullptr;
        if (value < node->value) node->left = delete_node(std::move(node->left), value);
        else if (value > node->value) node->right = delete_node(std::move(node->right), value);
        else {
            // node with only one child or no child
            if (!node->left) return std::move(node->right);
            else if (!node->right) return std::move(node->left);

            // node with two children: get inorder successor
            AVLNode* succ = min_node(node->right.get());
            node->value = succ->value;
            node->right = delete_node(std::move(node->right), succ->value);
        }

        update_height(node.get());
        int bf = balance_factor(node.get());

        // LL
        if (bf > 1 && balance_factor(node->left.get()) >= 0) return right_rotate(std::move(node));
        // LR
        if (bf > 1 && balance_factor(node->left.get()) < 0) {
            node->left = left_rotate(std::move(node->left));
            return right_rotate(std::move(node));
        }
        // RR
        if (bf < -1 && balance_factor(node->right.get()) <= 0) return left_rotate(std::move(node));
        // RL
        if (bf < -1 && balance_factor(node->right.get()) > 0) {
            node->right = right_rotate(std::move(node->right));
            return left_rotate(std::move(node));
        }

        return node;
    }

    void remove(int value) { root = delete_node(std::move(root), value); }

    // Preorder traversal collecting values
    void preorder(const AVLNode* node, std::vector<int>& out) const {
        if (!node) return;
        out.push_back(node->value);
        preorder(node->left.get(), out);
        preorder(node->right.get(), out);
    }

    std::vector<int> preorder() const { std::vector<int> out; preorder(root.get(), out); return out; }
};

// Demo main
int main() {
    AVLTree tree;
    std::vector<int> values = {10,20,30,40,50,25};
    for (int v : values) tree.insert(v);
    auto pre = tree.preorder();
    std::cout << "Preorder after inserts: ";
    for (int x : pre) std::cout << x << " ";
    std::cout << "\n";

    tree.remove(20);
    pre = tree.preorder();
    std::cout << "Preorder after removing 20: ";
    for (int x : pre) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
