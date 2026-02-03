/*
 * BINARY TREE IMPLEMENTATION
 * 
 * This file demonstrates a comprehensive binary tree implementation in C++:
 * - Binary tree node structure and operations
 * - Tree traversal algorithms (preorder, inorder, postorder, level-order)
 * - Tree balancing and height checking
 * - Recursive and iterative tree operations
 * - Memory management and tree construction
 * 
 * Learning Objectives:
 * - Understand binary tree data structure concepts
 * - Learn different tree traversal algorithms
 * - Master recursive tree operations
 * - Understand tree balancing techniques
 * - Learn level-order traversal (BFS) implementation
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of classes and objects
 * - Familiarity with pointers and dynamic memory
 * - Understanding of recursion
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <vector>    // For vector container
#include <cmath>     // For mathematical functions (abs, max)
using namespace std; // Using standard namespace

/*
 * BINARY TREE NODE CLASS
 * 
 * Represents a single node in a binary tree.
 * Each node contains:
 * - value: the data stored in the node
 * - left: pointer to left child node
 * - right: pointer to right child node
 * 
 * Key Concepts:
 * - Self-referential structure (contains pointers to same type)
 * - Constructor initializes node with given value
 * - Pointers are initialized to nullptr (no children initially)
 */
class Node {
public:
    int value;    // Data stored in this node
    Node* left;   // Pointer to left child node
    Node* right;  // Pointer to right child node

    /*
     * NODE CONSTRUCTOR
     * 
     * Creates a new node with the given value.
     * Initializes child pointers to nullptr (no children).
     * 
     * @param v The value to store in this node
     */
    Node(int v) {
        value = v;           // Store the value
        left = nullptr;      // No left child initially
        right = nullptr;     // No right child initially
    }
};

/*
 * BINARY TREE CLASS
 * 
 * Implements a binary search tree with various operations:
 * - Insertion and searching
 * - Multiple traversal methods
 * - Tree balancing
 * - Height checking
 * 
 * Key Concepts:
 * - Binary Search Tree property: left < root < right
 * - Recursive operations for tree manipulation
 * - Multiple traversal algorithms
 * - Tree balancing for optimal performance
 */
class BinaryTree {
private:
    Node* root;  // Pointer to the root node of the tree

    /*
     * RECURSIVE INSERT HELPER
     * 
     * Recursively inserts a value into the binary search tree.
     * Maintains the BST property: left child < parent < right child.
     * 
     * @param node Current node being examined
     * @param value Value to insert
     * @return Pointer to the (possibly new) node
     */
    Node* insert(Node* node, int value) {
        // Base case: if current position is empty, create new node
        if (node == nullptr) {
            return new Node(value);
        }
        
        // Recursive case: decide which subtree to insert into
        if (value < node->value) {
            // Insert into left subtree (smaller values go left)
            node->left = insert(node->left, value);
        } else {
            // Insert into right subtree (larger values go right)
            node->right = insert(node->right, value);
        }
        
        return node;  // Return the current node (unchanged)
    }

    // Traversal helpers
    void preorder(Node* node) {
        if (node) {
            cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->value << " ";
        }
    }

    // Store inorder traversal into array
    void storeInorder(Node* node, vector<int>& arr) {
        if (node) {
            storeInorder(node->left, arr);
            arr.push_back(node->value);
            storeInorder(node->right, arr);
        }
    }

    // Build balanced tree from sorted array
    Node* buildBalanced(vector<int>& arr, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        Node* node = new Node(arr[mid]);
        node->left = buildBalanced(arr, start, mid - 1);
        node->right = buildBalanced(arr, mid + 1, end);
        return node;
    }

    // Check balance: returns height, sets balanced flag
    int checkBalanced(Node* node, bool& balanced) {
        if (!node) return 0;
        int leftHeight = checkBalanced(node->left, balanced);
        int rightHeight = checkBalanced(node->right, balanced);
        if (abs(leftHeight - rightHeight) > 1) balanced = false;
        return max(leftHeight, rightHeight) + 1;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    // Insert
    void insert(int value) {
        root = insert(root, value);
    }

    // Build from array
    void buildFromList(const vector<int>& values) {
        for (int v : values) {
            insert(v);
        }
    }

    // Traversals
    // preorder: Root → Left → Right
    // inorder: Left → Root → Right
    // postorder: Left → Right → Root
    // level_order: BFS (using a simple list as queue).
    void preorder() {
        preorder(root);
        cout << endl;
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    // Level-order (BFS) without STL queue
    void levelOrder() {
        if (!root) return;

        Node* queue[1000];  // fixed size queue
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            Node* node = queue[front++];
            cout << node->value << " ";
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        cout << endl;
    }

    // Balance the tree
    void balance() {
        vector<int> arr;
        storeInorder(root, arr);
        root = buildBalanced(arr, 0, arr.size() - 1);
    }

    // Check if tree is balanced
    bool isBalanced() {
        bool balanced = true;
        checkBalanced(root, balanced);
        return balanced;
    }
};

int main() {
    vector<int> values = {10, 5, 20, 3, 7, 30, 25, 40};
    BinaryTree tree;
    tree.buildFromList(values);

    cout << "Preorder: ";
    tree.preorder();

    cout << "Inorder: ";
    tree.inorder();

    cout << "Postorder: ";
    tree.postorder();

    cout << "Level Order: ";
    tree.levelOrder();

    cout << "\nIs balanced before: " << (tree.isBalanced() ? "Yes" : "No") << endl;

    cout << "Balancing tree..." << endl;
    tree.balance();

    cout << "Preorder after balance: ";
    tree.preorder();

    cout << "Inorder after balance: ";
    tree.inorder();

    cout << "Postorder after balance: ";
    tree.postorder();

    cout << "Level Order after balance: ";
    tree.levelOrder();

    cout << "Is balanced after: " << (tree.isBalanced() ? "Yes" : "No") << endl;

    return 0;
}