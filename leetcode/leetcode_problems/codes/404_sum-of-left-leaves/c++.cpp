/*
 * Problem: Sum of Left Leaves
 * Difficulty: Easy
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
    int dfs(TreeNode* node, bool isLeft) {
        if (!node) {
            return 0;
        }
        
        if (!node->left && !node->right) {
            return isLeft ? node->val : 0;
        }
        
        return dfs(node->left, true) + dfs(node->right, false);
    }

public:
    int sumOfLeftLeaves(TreeNode* root) {
        return dfs(root, false);
    }
};