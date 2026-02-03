/*
 * Problem: Print Binary Tree
 * Difficulty: Medium
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
#include <cmath>

using namespace std;

class Solution {
private:
    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
    
    void fill(TreeNode* node, vector<vector<string>>& result, int level, int left, int right) {
        if (node == nullptr) {
            return;
        }
        
        int mid = (left + right) / 2;
        result[level][mid] = to_string(node->val);
        fill(node->left, result, level + 1, left, mid - 1);
        fill(node->right, result, level + 1, mid + 1, right);
    }

public:
    vector<vector<string>> printTree(TreeNode* root) {
        int height = getHeight(root);
        int width = (1 << height) - 1;
        vector<vector<string>> result(height, vector<string>(width, ""));
        
        fill(root, result, 0, 0, width - 1);
        return result;
    }
};