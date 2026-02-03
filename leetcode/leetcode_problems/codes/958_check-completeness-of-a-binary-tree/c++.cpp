/*
 * Problem: Check Completeness of a Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: BFS - check if all nodes before a null are non-null
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for queue
 */

#include <queue>

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
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        bool seenNull = false;
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node == nullptr) {
                seenNull = true;
            } else {
                if (seenNull) {
                    return false;
                }
                q.push(node->left);
                q.push(node->right);
            }
        }
        
        return true;
    }
};
