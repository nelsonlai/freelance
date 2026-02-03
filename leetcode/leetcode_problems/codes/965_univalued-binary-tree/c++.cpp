/*
 * Problem: Univalued Binary Tree
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: DFS - check if all nodes have the same value as root
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
    bool dfs(TreeNode* node, int val) {
        if (node == nullptr) {
            return true;
        }
        if (node->val != val) {
            return false;
        }
        return dfs(node->left, val) && dfs(node->right, val);
    }
    
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return dfs(root, root->val);
    }
};
