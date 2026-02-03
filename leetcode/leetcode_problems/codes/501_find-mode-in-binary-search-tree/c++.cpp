/*
 * Problem: Find Mode in Binary Search Tree
 * Difficulty: Easy
 * Tags: tree, search, stack
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
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

using namespace std;

class Solution {
private:
    unordered_map<int, int> count;
    
    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            count[node->val]++;
            inorder(node->right);
        }
    }

public:
    vector<int> findMode(TreeNode* root) {
        inorder(root);
        
        if (count.empty()) {
            return {};
        }
        
        int maxCount = 0;
        for (auto& entry : count) {
            maxCount = max(maxCount, entry.second);
        }
        
        vector<int> result;
        for (auto& entry : count) {
            if (entry.second == maxCount) {
                result.push_back(entry.first);
            }
        }
        
        return result;
    }
};