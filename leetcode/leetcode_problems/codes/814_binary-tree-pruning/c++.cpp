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
    bool hasOne(TreeNode* node) {
        if (node == nullptr) {
            return false;
        }
        bool leftHas = hasOne(node->left);
        bool rightHas = hasOne(node->right);
        if (!leftHas) {
            node->left = nullptr;
        }
        if (!rightHas) {
            node->right = nullptr;
        }
        return node->val == 1 || leftHas || rightHas;
    }

public:
    TreeNode* pruneTree(TreeNode* root) {
        return hasOne(root) ? root : nullptr;
    }
};
