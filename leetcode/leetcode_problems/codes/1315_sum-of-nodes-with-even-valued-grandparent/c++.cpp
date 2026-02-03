/*
 * Problem: Sum of Nodes with Even-Valued Grandparent
 * Difficulty: Medium
 * Tags: tree, dp, search
 * 
 * Approach: DFS - pass parent and grandparent values, sum if grandparent is even
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
public:
    int dfs(TreeNode* node, int parent, int grandparent) {
        if (!node) {
            return 0;
        }
        
        int total = 0;
        if (grandparent != -1 && grandparent % 2 == 0) {
            total += node->val;
        }
        
        total += dfs(node->left, node->val, parent);
        total += dfs(node->right, node->val, parent);
        return total;
    }
    
    int sumEvenGrandparent(TreeNode* root) {
        return dfs(root, -1, -1);
    }
};
