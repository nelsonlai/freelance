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

// Simple Binary Search Tree (BST) - C++ translation with comments
// Converted from a Python implementation; includes insert, traversals,
// balance-by-rebuilding, and simple checks. Designed for teaching.

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        if (!root) root = new Node(value);
        else _insert(root, value);
    }

    void _insert(Node* cur, int value) {
        if (value < cur->value) {
            if (cur->left) _insert(cur->left, value);
            else cur->left = new Node(value);
        } else {
            if (cur->right) _insert(cur->right, value);
            else cur->right = new Node(value);
        }
    }

    // Build from list convenience
    void build_from_list(const std::vector<int>& values) {
        for (int v : values) insert(v);
    }

    // Traversals
    // Depth-first
    // Preorder traversal (root-left-right)
    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Inorder traversal (left-root-right)
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

    // Postorder traversal (left-right-root)
    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->value << " ";
    }

    // Level order (BFS)
    void level_order() const {
        if (!root) return;
        std::vector<Node*> q{root};
        size_t idx = 0;
        while (idx < q.size()) {
            Node* n = q[idx++];
            std::cout << n->value << " ";
            if (n->left) q.push_back(n->left);
            if (n->right) q.push_back(n->right);
        }
    }

    // Balance by collecting inorder and rebuilding a minimal-height tree
    void _store_inorder(Node* node, std::vector<int>& out) const {
        if (!node) return;
        _store_inorder(node->left, out);
        out.push_back(node->value);
        _store_inorder(node->right, out);
    }

    Node* _build_balanced(const std::vector<int>& arr, int l, int r) {
        if (l > r) return nullptr;
        int mid = (l + r) / 2;
        Node* n = new Node(arr[mid]);
        n->left = _build_balanced(arr, l, mid-1);
        n->right = _build_balanced(arr, mid+1, r);
        return n;
    }

    void balance() {
        std::vector<int> vals;
        _store_inorder(root, vals);
        // Note: we leak old nodes here for brevity in a small teaching demo.
        // In production you'd delete old nodes or reconstruct in-place.
        root = _build_balanced(vals, 0, (int)vals.size()-1);
    }

    // Check if balanced (height-balanced) returning (height, balanced)
    std::pair<int,bool> _check_balanced(Node* node) const {
        if (!node) return {0,true};
        auto L = _check_balanced(node->left);
        auto R = _check_balanced(node->right);
        int h = std::max(L.first, R.first) + 1;
        bool bal = L.second && R.second && std::abs(L.first - R.first) <= 1;
        return {h, bal};
    }

    bool is_balanced() const { return _check_balanced(root).second; }
};

// Demo main
int main() {
    BinaryTree t;
    std::vector<int> vals = {32,23,12,56,78,12,34,5,3,2,9,7,10};
    t.build_from_list(vals);
    std::cout << "Is balanced before: " << (t.is_balanced() ? "yes" : "no") << "\n";
    t.balance();
    std::cout << "Is balanced after: " << (t.is_balanced() ? "yes" : "no") << "\n";
    std::cout << "Preorder: "; t.preorder(t.root); std::cout << "\n";
    std::cout << "Inorder: "; t.inorder(t.root); std::cout << "\n";
    std::cout << "Postorder: "; t.postorder(t.root); std::cout << "\n";
    std::cout << "Level order: "; t.level_order(); std::cout << "\n";
    return 0;
}
