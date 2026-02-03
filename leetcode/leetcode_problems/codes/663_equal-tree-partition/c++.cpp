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
    int getSum(TreeNode* node, unordered_set<int>& seen) {
        if (node == nullptr) {
            return 0;
        }
        
        int sum = node->val + getSum(node->left, seen) + getSum(node->right, seen);
        seen.insert(sum);
        return sum;
    }

public:
    bool checkEqualTree(TreeNode* root) {
        unordered_set<int> seen;
        int total = getSum(root, seen);
        seen.erase(total);
        return total % 2 == 0 && seen.find(total / 2) != seen.end();
    }
};
