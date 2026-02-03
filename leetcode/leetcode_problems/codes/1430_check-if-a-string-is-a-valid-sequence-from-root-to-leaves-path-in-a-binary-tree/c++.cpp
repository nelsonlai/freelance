/*
 * Problem: Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
 * Difficulty: Medium
 * Tags: array, string, tree, search
 * 
 * Approach: DFS - check if path matches array and ends at leaf
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
    bool dfs(TreeNode* node, vector<int>& arr, int idx) {
        if (!node || idx >= arr.size() || node->val != arr[idx]) {
            return false;
        }
        
        if (idx == arr.size() - 1) {
            return !node->left && !node->right;
        }
        
        return dfs(node->left, arr, idx + 1) || dfs(node->right, arr, idx + 1);
    }
    
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return dfs(root, arr, 0);
    }
};
