/*
 * Problem: Number of Good Leaf Nodes Pairs
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS - return list of distances to leaves, count pairs within distance
 * Time Complexity: O(n * distance^2) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
 */

#include <vector>
#include <algorithm>

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
    int count = 0;
    
    std::vector<int> dfs(TreeNode* node, int distance) {
        if (node == nullptr) {
            return {};
        }
        
        if (node->left == nullptr && node->right == nullptr) {
            return {1};
        }
        
        std::vector<int> leftDistances = dfs(node->left, distance);
        std::vector<int> rightDistances = dfs(node->right, distance);
        
        for (int leftDist : leftDistances) {
            for (int rightDist : rightDistances) {
                if (leftDist + rightDist <= distance) {
                    count++;
                }
            }
        }
        
        std::vector<int> result;
        for (int d : leftDistances) {
            if (d + 1 < distance) {
                result.push_back(d + 1);
            }
        }
        for (int d : rightDistances) {
            if (d + 1 < distance) {
                result.push_back(d + 1);
            }
        }
        
        return result;
    }

public:
    int countPairs(TreeNode* root, int distance) {
        count = 0;
        dfs(root, distance);
        return count;
    }
};