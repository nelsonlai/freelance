/*
 * Problem: Closest Binary Search Tree Value II
 * Difficulty: Hard
 * Tags: array, tree, search, stack, queue, heap
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
#include <deque>

using namespace std;

class Solution {
private:
    void inorder(TreeNode* node, double target, int k, deque<int>& result) {
        if (!node) {
            return;
        }
        
        inorder(node->left, target, k, result);
        
        if (result.size() < k) {
            result.push_back(node->val);
        } else {
            if (abs(node->val - target) < abs(result.front() - target)) {
                result.pop_front();
                result.push_back(node->val);
            } else {
                return;
            }
        }
        
        inorder(node->right, target, k, result);
    }

public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> result;
        inorder(root, target, k, result);
        return vector<int>(result.begin(), result.end());
    }
};