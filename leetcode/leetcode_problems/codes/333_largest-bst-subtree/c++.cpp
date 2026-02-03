/*
 * Problem: Largest BST Subtree
 * Difficulty: Medium
 * Tags: tree, dp, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) or O(n * m) for DP table
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
#include <vector>
#include <climits>

using namespace std;

class Solution {
private:
    vector<int> dfs(TreeNode* node) {
        if (!node) {
            return {0, INT_MAX, INT_MIN};
        }
        
        vector<int> left = dfs(node->left);
        vector<int> right = dfs(node->right);
        
        if (left[2] < node->val && node->val < right[1]) {
            return {left[0] + right[0] + 1, 
                   min(left[1], node->val), 
                   max(right[2], node->val)};
        }
        
        return {max(left[0], right[0]), INT_MIN, INT_MAX};
    }

public:
    int largestBSTSubtree(TreeNode* root) {
        return dfs(root)[0];
    }
};