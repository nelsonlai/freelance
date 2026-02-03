/*
 * Problem: Sum of Root To Leaf Binary Numbers
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: DFS - accumulate binary number from root to leaf, sum all leaf values
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
    int total = 0;
    
    void dfs(TreeNode* node, int current) {
        if (!node) {
            return;
        }
        
        current = current * 2 + node->val;
        
        if (!node->left && !node->right) {
            total += current;
        } else {
            dfs(node->left, current);
            dfs(node->right, current);
        }
    }
    
public:
    int sumRootToLeaf(TreeNode* root) {
        dfs(root, 0);
        return total;
    }
};