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

// Red-Black Tree - C++ translation of the provided Python implementation.
// This is an educational implementation with comments explaining key
// invariants and the insert/fixup algorithm. It uses raw pointers and
// a sentinel NIL node to simplify boundary handling.

#include <iostream>
#include <string>
#include <vector>

enum Color { RED, BLACK };

struct RBNode {
    int value;
    Color color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    RBNode(int v, Color c, RBNode* nil) : value(v), color(c), parent(nil), left(nil), right(nil) {}
};

// A global sentinel NIL node simplifies checks by avoiding nullptrs.
static RBNode* NIL = nullptr;

class RedBlackTree {
public:
    RBNode* root;
    RedBlackTree() {
        if (!NIL) NIL = new RBNode(0, BLACK, nullptr); // single shared sentinel
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    // Left rotate x
    void left_rotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Right rotate x
    void right_rotate(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insert(int value) {
        RBNode* z = new RBNode(value, RED, NIL);
        RBNode* y = NIL;
        RBNode* x = root;
        while (x != NIL) {
            y = x;
            if (z->value < x->value) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (z->value < y->value) y->left = z;
        else y->right = z;

        z->left = NIL; z->right = NIL; z->color = RED;
        insert_fixup(z);
    }

    void insert_fixup(RBNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->right) {
                RBNode* u = z->parent->parent->left; // uncle
                if (u->color == RED) {
                    u->color = BLACK;
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            } else {
                RBNode* u = z->parent->parent->right; // uncle
                if (u->color == RED) {
                    u->color = BLACK;
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            }
            if (z == root) break;
        }
        root->color = BLACK;
    }

    // Utility to print the tree (inorder) with colors for debugging/teaching
    void inorder_print(RBNode* node) const {
        if (node == NIL) return;
        inorder_print(node->left);
        std::cout << node->value << (node->color == RED ? "(R) " : "(B) ");
        inorder_print(node->right);
    }
};

int main() {
    RedBlackTree rb;
    std::vector<int> vals = {55,40,65,60,75,57};
    for (int v : vals) rb.insert(v);
    std::cout << "Inorder with colors: "; rb.inorder_print(rb.root); std::cout << "\n";
    return 0;
}
