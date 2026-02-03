/*
 * Problem: Two Sum BSTs
 * Difficulty: Medium
 * Tags: array, tree, search, stack
 * 
 * Approach: Store values from one BST in set, search for complement in other BST
 * Time Complexity: O(n + m) where n, m are sizes of trees
 * Space Complexity: O(n) for set
 */

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
#include <unordered_set>

using namespace std;

class Solution {
public:
    void collectValues(TreeNode* node, unordered_set<int>& values) {
        if (!node) {
            return;
        }
        values.insert(node->val);
        collectValues(node->left, values);
        collectValues(node->right, values);
    }
    
    bool searchComplement(TreeNode* node, unordered_set<int>& complementSet, int target) {
        if (!node) {
            return false;
        }
        if (complementSet.count(target - node->val)) {
            return true;
        }
        return searchComplement(node->left, complementSet, target) 
            || searchComplement(node->right, complementSet, target);
    }
    
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        unordered_set<int> values1;
        collectValues(root1, values1);
        return searchComplement(root2, values1, target);
    }
};
