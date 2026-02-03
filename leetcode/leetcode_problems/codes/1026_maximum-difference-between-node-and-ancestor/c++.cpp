/*
 * Problem: Maximum Difference Between Node and Ancestor
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - track min and max values in path, update max difference
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
class Solution {
private:
    int maxDiff = 0;
    
    void dfs(TreeNode* node, int minVal, int maxVal) {
        if (!node) {
            return;
        }
        
        minVal = min(minVal, node->val);
        maxVal = max(maxVal, node->val);
        maxDiff = max(maxDiff, maxVal - minVal);
        
        dfs(node->left, minVal, maxVal);
        dfs(node->right, minVal, maxVal);
    }
    
public:
    int maxAncestorDiff(TreeNode* root) {
        dfs(root, root->val, root->val);
        return maxDiff;
    }
};