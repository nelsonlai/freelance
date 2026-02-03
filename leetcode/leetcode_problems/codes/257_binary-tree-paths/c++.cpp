/*
 * Problem: Binary Tree Paths
 * Difficulty: Easy
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
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
#include <string>

using namespace std;

class Solution {
private:
    void dfs(TreeNode* node, vector<string>& path, vector<string>& result) {
        if (!node) {
            return;
        }
        
        path.push_back(to_string(node->val));
        
        if (!node->left && !node->right) {
            string pathStr;
            for (int i = 0; i < path.size(); i++) {
                if (i > 0) pathStr += "->";
                pathStr += path[i];
            }
            result.push_back(pathStr);
        } else {
            dfs(node->left, path, result);
            dfs(node->right, path, result);
        }
        
        path.pop_back();
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<string> path;
        dfs(root, path, result);
        return result;
    }
};