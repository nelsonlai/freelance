/*
 * Problem: House Robber III
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
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> dfs(TreeNode* node) {
        if (!node) {
            return {0, 0};
        }
        
        vector<int> left = dfs(node->left);
        vector<int> right = dfs(node->right);
        
        int rob = node->val + left[1] + right[1];
        int notRob = max(left[0], left[1]) + max(right[0], right[1]);
        
        return {rob, notRob};
    }

public:
    int rob(TreeNode* root) {
        vector<int> result = dfs(root);
        return max(result[0], result[1]);
    }
};