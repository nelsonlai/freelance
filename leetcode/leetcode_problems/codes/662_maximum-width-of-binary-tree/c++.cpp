#include <vector>
#include <queue>
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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        queue<pair<TreeNode*, long long>> q;
        q.push({root, 0});
        int maxWidth = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            long long leftPos = q.front().second;
            
            for (int i = 0; i < levelSize; i++) {
                auto [node, pos] = q.front();
                q.pop();
                
                if (node->left != nullptr) {
                    q.push({node->left, 2 * pos});
                }
                if (node->right != nullptr) {
                    q.push({node->right, 2 * pos + 1});
                }
            }
            
            if (!q.empty()) {
                long long rightPos = q.back().second;
                maxWidth = max(maxWidth, (int)(rightPos - leftPos + 1));
            }
        }
        
        return maxWidth;
    }
};
