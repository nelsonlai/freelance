/*
 * Problem: Count Complete Tree Nodes
 * Difficulty: Easy
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
    int getHeight(TreeNode* root) {
        int height = 0;
        while (root) {
            height++;
            root = root->left;
        }
        return height;
    }

public:
    int countNodes(TreeNode* root) {
        if (!root) {
            return 0;
        }
        
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        
        if (leftHeight == rightHeight) {
            return (1 << leftHeight) + countNodes(root->right);
        } else {
            return (1 << rightHeight) + countNodes(root->left);
        }
    }
};