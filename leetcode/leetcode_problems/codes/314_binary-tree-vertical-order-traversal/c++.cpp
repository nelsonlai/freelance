/*
 * Problem: Binary Tree Vertical Order Traversal
 * Difficulty: Medium
 * Tags: tree, hash, sort, search
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
#include <queue>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) {
            return {};
        }
        
        map<int, vector<int>> columnMap;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();
            
            columnMap[col].push_back(node->val);
            
            if (node->left) {
                q.push({node->left, col - 1});
            }
            if (node->right) {
                q.push({node->right, col + 1});
            }
        }
        
        vector<vector<int>> result;
        for (auto& [col, values] : columnMap) {
            result.push_back(values);
        }
        return result;
    }
};