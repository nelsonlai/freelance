/*
 * Problem: Boundary of Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

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
#include <vector>

using namespace std;

class Solution {
private:
    void leftBoundary(TreeNode* node, vector<int>& result) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return;
        }
        result.push_back(node->val);
        if (node->left != nullptr) {
            leftBoundary(node->left, result);
        } else {
            leftBoundary(node->right, result);
        }
    }
    
    void leaves(TreeNode* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            result.push_back(node->val);
            return;
        }
        leaves(node->left, result);
        leaves(node->right, result);
    }
    
    void rightBoundary(TreeNode* node, vector<int>& result) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return;
        }
        if (node->right != nullptr) {
            rightBoundary(node->right, result);
        } else {
            rightBoundary(node->left, result);
        }
        result.push_back(node->val);
    }

public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        
        if (root->left == nullptr && root->right == nullptr) {
            return {root->val};
        }
        
        vector<int> result;
        result.push_back(root->val);
        
        if (root->left != nullptr) {
            leftBoundary(root->left, result);
        }
        leaves(root, result);
        if (root->right != nullptr) {
            rightBoundary(root->right, result);
        }
        
        return result;
    }
};