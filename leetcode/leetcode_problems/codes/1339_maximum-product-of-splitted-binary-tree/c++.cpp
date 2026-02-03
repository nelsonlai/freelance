/*
 * Problem: Maximum Product of Splitted Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: Calculate total sum, DFS to find subtree sums, maximize product
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
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
    const int MOD = 1e9 + 7;
    long long maxProduct = 0;
    long long total = 0;
    
    long long totalSum(TreeNode* node) {
        if (!node) {
            return 0;
        }
        return node->val + totalSum(node->left) + totalSum(node->right);
    }
    
    long long dfs(TreeNode* node) {
        if (!node) {
            return 0;
        }
        
        long long subtreeSum = node->val + dfs(node->left) + dfs(node->right);
        long long product = subtreeSum * (total - subtreeSum);
        maxProduct = max(maxProduct, product);
        return subtreeSum;
    }
    
    int maxProduct(TreeNode* root) {
        total = totalSum(root);
        dfs(root);
        return (int) (maxProduct % MOD);
    }
};
