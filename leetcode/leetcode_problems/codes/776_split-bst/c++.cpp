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
    vector<TreeNode*> splitBST(TreeNode* root, int target) {
        if (root == nullptr) {
            return {nullptr, nullptr};
        }
        
        if (root->val <= target) {
            vector<TreeNode*> result = splitBST(root->right, target);
            root->right = result[0];
            return {root, result[1]};
        } else {
            vector<TreeNode*> result = splitBST(root->left, target);
            root->left = result[1];
            return {result[0], root};
        }
    }
};
