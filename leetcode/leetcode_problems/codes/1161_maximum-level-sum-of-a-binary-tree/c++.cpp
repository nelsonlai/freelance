/*
 * Problem: Maximum Level Sum of a Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: BFS level-order traversal, track sum for each level
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(w) where w is maximum width of tree
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
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if (!root) {
            return 0;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        int maxSum = INT_MIN;
        int maxLevel = 1;
        int level = 1;
        
        while (!q.empty()) {
            int levelSum = 0;
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                levelSum += node->val;
                
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            
            if (levelSum > maxSum) {
                maxSum = levelSum;
                maxLevel = level;
            }
            
            level++;
        }
        
        return maxLevel;
    }
};
