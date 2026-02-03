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
    int maxDiameter = 0;
    
    int depth(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int left = depth(node->left);
        int right = depth(node->right);
        maxDiameter = max(maxDiameter, left + right);
        
        return max(left, right) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return maxDiameter;
    }
};
