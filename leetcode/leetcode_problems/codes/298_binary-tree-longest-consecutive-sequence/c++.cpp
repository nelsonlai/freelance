/*
 * Problem: Binary Tree Longest Consecutive Sequence
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
class Solution {
private:
    int maxLength = 0;
    
    void dfs(TreeNode* node, int* parentVal, int length) {
        if (!node) {
            return;
        }
        
        if (parentVal != nullptr && node->val == *parentVal + 1) {
            length++;
        } else {
            length = 1;
        }
        
        maxLength = max(maxLength, length);
        
        int val = node->val;
        dfs(node->left, &val, length);
        dfs(node->right, &val, length);
    }

public:
    int longestConsecutive(TreeNode* root) {
        dfs(root, nullptr, 0);
        return maxLength;
    }
};