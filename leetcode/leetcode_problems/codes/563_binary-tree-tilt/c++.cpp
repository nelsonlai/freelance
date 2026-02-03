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
    int totalTilt = 0;
    
    int sumTree(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftSum = sumTree(node->left);
        int rightSum = sumTree(node->right);
        totalTilt += abs(leftSum - rightSum);
        
        return node->val + leftSum + rightSum;
    }

public:
    int findTilt(TreeNode* root) {
        sumTree(root);
        return totalTilt;
    }
};
