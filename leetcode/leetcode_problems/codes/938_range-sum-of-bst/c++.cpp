/*
 * Problem: Range Sum of BST
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: DFS traversal, skip subtrees outside range
 * Time Complexity: O(n) worst case, but can be optimized to O(log n) for balanced tree
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
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return 0;
        }
        
        int total = 0;
        if (low <= root->val && root->val <= high) {
            total += root->val;
        }
        
        if (root->val > low) {
            total += rangeSumBST(root->left, low, high);
        }
        if (root->val < high) {
            total += rangeSumBST(root->right, low, high);
        }
        
        return total;
    }
};
