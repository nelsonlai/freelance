/*
 * Problem: Delete Nodes And Return Forest
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
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
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
private:
    TreeNode* dfs(TreeNode* node, bool isRoot, unordered_set<int>& toDeleteSet, vector<TreeNode*>& result) {
        if (!node) {
            return nullptr;
        }
        
        bool shouldDelete = toDeleteSet.find(node->val) != toDeleteSet.end();
        
        if (isRoot && !shouldDelete) {
            result.push_back(node);
        }
        
        node->left = dfs(node->left, shouldDelete, toDeleteSet, result);
        node->right = dfs(node->right, shouldDelete, toDeleteSet, result);
        
        return shouldDelete ? nullptr : node;
    }

public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> toDeleteSet(to_delete.begin(), to_delete.end());
        vector<TreeNode*> result;
        dfs(root, true, toDeleteSet, result);
        return result;
    }
};