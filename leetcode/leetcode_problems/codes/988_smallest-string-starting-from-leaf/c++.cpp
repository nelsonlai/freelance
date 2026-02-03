/*
 * Problem: Smallest String Starting From Leaf
 * Difficulty: Medium
 * Tags: string, tree, graph, search
 * 
 * Approach: DFS - collect all root-to-leaf strings, return lexicographically smallest
 * Time Complexity: O(n * h) where h is height
 * Space Complexity: O(h) for recursion stack
 */

#include <string>
#include <algorithm>

using namespace std;

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
    string result = "";
    
    void dfs(TreeNode* node, string path) {
        if (node == nullptr) {
            return;
        }
        
        path += (char)('a' + node->val);
        
        if (node->left == nullptr && node->right == nullptr) {
            string s = path;
            reverse(s.begin(), s.end());
            if (result.empty() || s < result) {
                result = s;
            }
        } else {
            dfs(node->left, path);
            dfs(node->right, path);
        }
    }
    
public:
    string smallestFromLeaf(TreeNode* root) {
        dfs(root, "");
        return result;
    }
};
