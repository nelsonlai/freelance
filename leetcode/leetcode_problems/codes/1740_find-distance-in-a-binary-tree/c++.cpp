/*
 * Problem: Find Distance in a Binary Tree
 * Difficulty: Medium
 * Tags: tree, hash, search
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    TreeNode* findLCA(TreeNode* node, int p, int q) {
        if (!node || node->val == p || node->val == q) {
            return node;
        }
        
        TreeNode* left = findLCA(node->left, p, q);
        TreeNode* right = findLCA(node->right, p, q);
        
        if (left && right) {
            return node;
        }
        return left ? left : right;
    }
    
    int distance(TreeNode* node, int target, int dist) {
        if (!node) {
            return -1;
        }
        if (node->val == target) {
            return dist;
        }
        
        int left = distance(node->left, target, dist + 1);
        if (left != -1) {
            return left;
        }
        return distance(node->right, target, dist + 1);
    }
    
public:
    int findDistance(TreeNode* root, int p, int q) {
        TreeNode* lca = findLCA(root, p, q);
        return distance(lca, p, 0) + distance(lca, q, 0);
    }
};