/*
 * Problem: Find All The Lonely Nodes
 * Difficulty: Easy
 * Tags: array, tree, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
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
class Solution {
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, vector<int>& result) {
        if (!node) {
            return;
        }
        
        if (node->left && !node->right) {
            result.push_back(node->left->val);
        } else if (node->right && !node->left) {
            result.push_back(node->right->val);
        }
        
        dfs(node->left, result);
        dfs(node->right, result);
    }
};