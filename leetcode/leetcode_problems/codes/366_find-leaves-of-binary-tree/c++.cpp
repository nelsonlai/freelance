/*
 * Problem: Find Leaves of Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
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
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int dfs(TreeNode* node, vector<vector<int>>& result) {
        if (!node) {
            return -1;
        }
        
        int leftHeight = dfs(node->left, result);
        int rightHeight = dfs(node->right, result);
        int height = max(leftHeight, rightHeight) + 1;
        
        if (height >= result.size()) {
            result.push_back({});
        }
        result[height].push_back(node->val);
        
        return height;
    }

public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        dfs(root, result);
        return result;
    }
};