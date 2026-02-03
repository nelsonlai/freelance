/*
 * Problem: Clone Binary Tree With Random Pointer
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     Node *left;
 *     Node *right;
 *     Node *random;
 *     Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
 * };
 */

#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<Node*, NodeCopy*> mapping;
    
    NodeCopy* clone(Node* node) {
        if (!node) {
            return nullptr;
        }
        
        if (mapping.find(node) != mapping.end()) {
            return mapping[node];
        }
        
        NodeCopy* new_node = new NodeCopy(node->val);
        mapping[node] = new_node;
        new_node->left = clone(node->left);
        new_node->right = clone(node->right);
        new_node->random = clone(node->random);
        
        return new_node;
    }
    
public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        mapping.clear();
        return clone(root);
    }
};