/*
 * Problem: Maximum Average Subtree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - calculate sum and count for each subtree, track maximum average
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
public:
    double maxAvg = 0.0;
    
    pair<int, int> dfs(TreeNode* node) {
        if (!node) {
            return {0, 0}; // {sum, count}
        }
        
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        int totalSum = left.first + right.first + node->val;
        int totalCount = left.second + right.second + 1;
        double avg = (double) totalSum / totalCount;
        maxAvg = max(maxAvg, avg);
        
        return {totalSum, totalCount};
    }
    
    double maximumAverageSubtree(TreeNode* root) {
        maxAvg = 0.0;
        dfs(root);
        return maxAvg;
    }
};
