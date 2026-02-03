#include <unordered_set>

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
    bool dfs(TreeNode* node, int k, unordered_set<int>& seen) {
        if (node == nullptr) {
            return false;
        }
        
        if (seen.find(k - node->val) != seen.end()) {
            return true;
        }
        
        seen.insert(node->val);
        return dfs(node->left, k, seen) || dfs(node->right, k, seen);
    }

public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> seen;
        return dfs(root, k, seen);
    }
};
