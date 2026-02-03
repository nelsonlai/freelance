/*
 * Problem: Merge BSTs to Create Single BST
 * Difficulty: Hard
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
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

class Solution {
private:
    void merge(TreeNode* node, unordered_map<int, TreeNode*>& valToNode) {
        if (!node) return;
        
        if (node->left && valToNode.find(node->left->val) != valToNode.end()) {
            node->left = valToNode[node->left->val];
            valToNode.erase(node->left->val);
            merge(node->left, valToNode);
        }
        
        if (node->right && valToNode.find(node->right->val) != valToNode.end()) {
            node->right = valToNode[node->right->val];
            valToNode.erase(node->right->val);
            merge(node->right, valToNode);
        }
    }
    
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    }
    
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, TreeNode*> valToNode;
        unordered_set<int> leafVals;
        
        for (TreeNode* tree : trees) {
            valToNode[tree->val] = tree;
            if (tree->left) leafVals.insert(tree->left->val);
            if (tree->right) leafVals.insert(tree->right->val);
        }
        
        TreeNode* root = nullptr;
        for (TreeNode* tree : trees) {
            if (leafVals.find(tree->val) == leafVals.end()) {
                if (root) return nullptr;
                root = tree;
            }
        }
        
        if (!root) return nullptr;
        
        merge(root, valToNode);
        
        if (valToNode.size() > 1) return nullptr;
        
        if (validate(root, LONG_MIN, LONG_MAX)) {
            return root;
        }
        return nullptr;
    }
};