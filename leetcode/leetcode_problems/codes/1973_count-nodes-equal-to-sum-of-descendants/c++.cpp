/*
 * Problem: Count Nodes Equal to Sum of Descendants
 * Difficulty: Medium
 * Tags: tree, search, DFS
 * 
 * Approach: DFS to calculate sum of descendants, count nodes where val equals sum
 * Time Complexity: O(n) where n is nodes
 * Space Complexity: O(h) for recursion stack
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

using namespace std;

class Solution {
private:
    int count = 0;
    
    long long dfs(TreeNode* node) {
        if (!node) {
            return 0;
        }
        
        long long leftSum = dfs(node->left);
        long long rightSum = dfs(node->right);
        long long descendantsSum = leftSum + rightSum;
        
        if (node->val == descendantsSum) {
            count++;
        }
        
        return node->val + descendantsSum;
    }
    
public:
    int equalToDescendants(TreeNode* root) {
        dfs(root);
        return count;
    }
};
