/*
 * Problem: Deepest Leaves Sum
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: BFS - find deepest level, sum all nodes at that level
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for queue
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

using namespace std;

class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int levelSum = 0;
        
        while (!q.empty()) {
            levelSum = 0;
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
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
        }
        
        return levelSum;
    }
};
