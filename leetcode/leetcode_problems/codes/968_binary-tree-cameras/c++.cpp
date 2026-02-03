/*
 * Problem: Binary Tree Cameras
 * Difficulty: Hard
 * Tags: tree, dp, search
 * 
 * Approach: Greedy DFS - place cameras at parent of uncovered leaves
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
    int cameras = 0;
    
    // 0: uncovered, 1: covered, 2: has camera
    int dfs(TreeNode* node) {
        if (node == nullptr) {
            return 1; // covered
        }
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        if (left == 0 || right == 0) {
            cameras++;
            return 2; // place camera
        }
        
        if (left == 2 || right == 2) {
            return 1; // covered by child camera
        }
        
        return 0; // uncovered
    }
    
public:
    int minCameraCover(TreeNode* root) {
        if (dfs(root) == 0) {
            cameras++;
        }
        return cameras;
    }
};
