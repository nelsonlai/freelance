/*
 * Problem: Count Univalue Subtrees
 * Difficulty: Medium
 * Tags: tree, search
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
class Solution {
private:
    int count = 0;
    
    bool isUnival(TreeNode* node) {
        if (!node) {
            return true;
        }
        
        bool left = isUnival(node->left);
        bool right = isUnival(node->right);
        
        if (!left || !right) {
            return false;
        }
        
        if (node->left && node->left->val != node->val) {
            return false;
        }
        if (node->right && node->right->val != node->val) {
            return false;
        }
        
        count++;
        return true;
    }

public:
    int countUnivalSubtrees(TreeNode* root) {
        isUnival(root);
        return count;
    }
};