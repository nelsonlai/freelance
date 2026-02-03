#include <vector>

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
    void inorder(TreeNode* node, vector<int>& values) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, values);
        values.push_back(node->val);
        inorder(node->right, values);
    }

public:
    TreeNode* increasingBST(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        
        TreeNode* result = new TreeNode(values[0]);
        TreeNode* current = result;
        for (int i = 1; i < values.size(); i++) {
            current->right = new TreeNode(values[i]);
            current = current->right;
        }
        return result;
    }
};
