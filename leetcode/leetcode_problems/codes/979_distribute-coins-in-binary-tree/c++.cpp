/*
 * Problem: Distribute Coins in Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - return excess coins from subtree, moves = sum of absolute excess
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
    int moves = 0;
    
    int dfs(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftExcess = dfs(node->left);
        int rightExcess = dfs(node->right);
        
        moves += abs(leftExcess) + abs(rightExcess);
        
        return node->val + leftExcess + rightExcess - 1;
    }
    
public:
    int distributeCoins(TreeNode* root) {
        dfs(root);
        return moves;
    }
};
