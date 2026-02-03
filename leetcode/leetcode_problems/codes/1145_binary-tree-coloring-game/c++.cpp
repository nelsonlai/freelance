/*
 * Problem: Binary Tree Coloring Game
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: Find node x, calculate sizes of left, right, and parent subtrees
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
public:
    int leftSize = 0;
    int rightSize = 0;
    
    int dfs(TreeNode* node, int x) {
        if (!node) {
            return 0;
        }
        
        int left = dfs(node->left, x);
        int right = dfs(node->right, x);
        
        if (node->val == x) {
            leftSize = left;
            rightSize = right;
        }
        
        return left + right + 1;
    }
    
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        leftSize = 0;
        rightSize = 0;
        dfs(root, x);
        int parentSize = n - leftSize - rightSize - 1;
        
        return max({leftSize, rightSize, parentSize}) > n / 2;
    }
};
