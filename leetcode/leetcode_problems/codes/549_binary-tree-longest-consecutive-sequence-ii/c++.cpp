#include <vector>
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
    int maxLength = 0;
    
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) {
            return {0, 0};
        }
        
        int inc = 1, dec = 1;
        
        if (node->left != nullptr) {
            auto left = dfs(node->left);
            if (node->val == node->left->val + 1) {
                inc = max(inc, left.first + 1);
            }
            if (node->val == node->left->val - 1) {
                dec = max(dec, left.second + 1);
            }
        }
        
        if (node->right != nullptr) {
            auto right = dfs(node->right);
            if (node->val == node->right->val + 1) {
                inc = max(inc, right.first + 1);
            }
            if (node->val == node->right->val - 1) {
                dec = max(dec, right.second + 1);
            }
        }
        
        maxLength = max(maxLength, inc + dec - 1);
        return {inc, dec};
    }

public:
    int longestConsecutive(TreeNode* root) {
        dfs(root);
        return maxLength;
    }
};
