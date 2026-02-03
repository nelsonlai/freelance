#include <climits>
#include <algorithm>

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
    long long dfs(TreeNode* node, int rootVal) {
        if (node == nullptr) {
            return LLONG_MAX;
        }
        
        if (node->val > rootVal) {
            return node->val;
        }
        
        long long left = dfs(node->left, rootVal);
        long long right = dfs(node->right, rootVal);
        
        return min(left, right);
    }

public:
    int findSecondMinimumValue(TreeNode* root) {
        if (root == nullptr) {
            return -1;
        }
        
        long long result = dfs(root, root->val);
        return result == LLONG_MAX ? -1 : (int)result;
    }
};
