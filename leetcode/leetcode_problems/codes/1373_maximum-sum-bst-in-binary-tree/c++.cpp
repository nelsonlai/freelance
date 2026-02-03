/*
 * Problem: Maximum Sum BST in Binary Tree
 * Difficulty: Hard
 * Tags: tree, dp, search
 * 
 * Approach: DFS - return (isBST, min, max, sum) for each subtree
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
private:
    int maxSum = 0;
    
    struct Result {
        bool isBST;
        int minVal;
        int maxVal;
        int sum;
    };
    
    Result dfs(TreeNode* node) {
        if (!node) {
            return {true, INT_MAX, INT_MIN, 0};
        }
        
        Result left = dfs(node->left);
        Result right = dfs(node->right);
        
        if (left.isBST && right.isBST && left.maxVal < node->val && node->val < right.minVal) {
            int totalSum = left.sum + right.sum + node->val;
            maxSum = max(maxSum, totalSum);
            return {true, min(left.minVal, node->val), max(right.maxVal, node->val), totalSum};
        }
        
        return {false, 0, 0, 0};
    }
    
public:
    int maxSumBST(TreeNode* root) {
        dfs(root);
        return maxSum;
    }
};
