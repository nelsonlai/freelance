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
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> result;
        if (n % 2 == 0) {
            return result;
        }
        if (n == 1) {
            result.push_back(new TreeNode(0));
            return result;
        }
        
        for (int i = 1; i < n; i += 2) {
            vector<TreeNode*> lefts = allPossibleFBT(i);
            vector<TreeNode*> rights = allPossibleFBT(n - 1 - i);
            for (TreeNode* left : lefts) {
                for (TreeNode* right : rights) {
                    TreeNode* root = new TreeNode(0);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        return result;
    }
};
