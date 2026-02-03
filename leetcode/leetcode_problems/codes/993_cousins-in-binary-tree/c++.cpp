/*
 * Problem: Cousins in Binary Tree
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: BFS - find depth and parent of x and y, check if same depth but different parents
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for queue
 */

#include <queue>
#include <tuple>

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
    bool isCousins(TreeNode* root, int x, int y) {
        TreeNode* xParent = nullptr, *yParent = nullptr;
        int xDepth = -1, yDepth = -1;
        
        queue<tuple<TreeNode*, TreeNode*, int>> q;
        q.push({root, nullptr, 0});
        
        while (!q.empty()) {
            auto [node, parent, depth] = q.front();
            q.pop();
            
            if (node->val == x) {
                xParent = parent;
                xDepth = depth;
            }
            if (node->val == y) {
                yParent = parent;
                yDepth = depth;
            }
            
            if (node->left) {
                q.push({node->left, node, depth + 1});
            }
            if (node->right) {
                q.push({node->right, node, depth + 1});
            }
        }
        
        return xDepth == yDepth && xParent != yParent;
    }
};
