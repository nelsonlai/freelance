/*
 * Problem: Pseudo-Palindromic Paths in a Binary Tree
 * Difficulty: Medium
 * Tags: string, tree, search
 * 
 * Approach: DFS - track digit counts, check if at most one odd count at leaf
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
    int dfs(TreeNode* node, vector<int>& count) {
        if (!node) {
            return 0;
        }
        
        count[node->val]++;
        
        if (!node->left && !node->right) {
            int oddCount = 0;
            for (int c : count) {
                if (c % 2 == 1) {
                    oddCount++;
                }
            }
            count[node->val]--;
            return oddCount <= 1 ? 1 : 0;
        }
        
        int result = dfs(node->left, count) + dfs(node->right, count);
        count[node->val]--;
        return result;
    }
    
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        vector<int> count(10, 0);
        return dfs(root, count);
    }
};
