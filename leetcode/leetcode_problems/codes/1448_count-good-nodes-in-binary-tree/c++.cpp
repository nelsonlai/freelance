/*
 * Problem: Count Good Nodes in Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - track max value from root, count nodes >= max
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
    int dfs(TreeNode* node, int maxVal) {
        if (!node) {
            return 0;
        }
        
        int count = node->val >= maxVal ? 1 : 0;
        int newMax = std::max(maxVal, node->val);
        count += dfs(node->left, newMax);
        count += dfs(node->right, newMax);
        
        return count;
    }
    
public:
    int goodNodes(TreeNode* root) {
        return dfs(root, root->val);
    }
};
