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
    vector<int> getLeaves(TreeNode* node) {
        vector<int> result;
        if (node == nullptr) {
            return result;
        }
        if (node->left == nullptr && node->right == nullptr) {
            result.push_back(node->val);
            return result;
        }
        vector<int> left = getLeaves(node->left);
        vector<int> right = getLeaves(node->right);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }

public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        return getLeaves(root1) == getLeaves(root2);
    }
};
