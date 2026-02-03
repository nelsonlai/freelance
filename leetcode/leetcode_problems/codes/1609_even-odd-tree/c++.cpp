/*
 * Problem: Even Odd Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
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
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int size = q.size();
            int prev = -1;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (level % 2 == 0) {
                    if (node->val % 2 == 0) {
                        return false;
                    }
                    if (prev != -1 && node->val <= prev) {
                        return false;
                    }
                } else {
                    if (node->val % 2 == 1) {
                        return false;
                    }
                    if (prev != -1 && node->val >= prev) {
                        return false;
                    }
                }
                
                prev = node->val;
                
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            
            level++;
        }
        
        return true;
    }
};