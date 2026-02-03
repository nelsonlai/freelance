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
    TreeNode* build(vector<int>& pre, int preStart, int preEnd, vector<int>& post, int postStart, int postEnd) {
        if (preStart > preEnd) {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(pre[preStart]);
        if (preStart == preEnd) {
            return root;
        }
        
        int L = 0;
        for (int i = postStart; i <= postEnd; i++) {
            if (post[i] == pre[preStart + 1]) {
                L = i - postStart + 1;
                break;
            }
        }
        
        root->left = build(pre, preStart + 1, preStart + L, post, postStart, postStart + L - 1);
        root->right = build(pre, preStart + L + 1, preEnd, post, postStart + L, postEnd - 1);
        return root;
    }

public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        return build(preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
};
