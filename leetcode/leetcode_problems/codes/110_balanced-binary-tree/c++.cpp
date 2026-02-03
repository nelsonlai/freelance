/*
 * Problem: Balanced Binary Tree
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
#include <algorithm>
#include <cmath>
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
    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftHeight = getHeight(node->left);
        if (leftHeight == -1) {
            return -1;
        }
        
        int rightHeight = getHeight(node->right);
        if (rightHeight == -1) {
            return -1;
        }
        
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        
        return 1 + max(leftHeight, rightHeight);
    }
    
public:
    bool isBalanced(TreeNode* root) {
        return getHeight(root) != -1;
    }
};