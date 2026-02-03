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
    void dfs(TreeNode* node, int val, int targetDepth, int currentDepth) {
        if (node == nullptr) {
            return;
        }
        
        if (currentDepth == targetDepth - 1) {
            TreeNode* left = new TreeNode(val);
            TreeNode* right = new TreeNode(val);
            left->left = node->left;
            right->right = node->right;
            node->left = left;
            node->right = right;
        } else {
            dfs(node->left, val, targetDepth, currentDepth + 1);
            dfs(node->right, val, targetDepth, currentDepth + 1);
        }
    }

public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            TreeNode* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        
        dfs(root, val, depth, 1);
        return root;
    }
};
