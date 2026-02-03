/*
 * Problem: Binary Search Tree Iterator II
 * Difficulty: Medium
 * Tags: tree, search, stack
 * 
 * Approach: Store all nodes in vector via inorder traversal, track current index
 * Time Complexity: O(n) for init, O(1) for operations
 * Space Complexity: O(n) for node vector
 */

#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class BSTIterator {
private:
    std::vector<int> nodes;
    int idx;

    void inorder(TreeNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            nodes.push_back(node->val);
            inorder(node->right);
        }
    }

public:
    BSTIterator(TreeNode* root) {
        idx = -1;
        inorder(root);
    }
    
    bool hasNext() {
        return idx < (int)nodes.size() - 1;
    }
    
    int next() {
        idx++;
        return nodes[idx];
    }
    
    bool hasPrev() {
        return idx > 0;
    }
    
    int prev() {
        idx--;
        return nodes[idx];
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */