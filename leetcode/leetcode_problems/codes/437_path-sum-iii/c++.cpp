/*
 * Problem: Path Sum III
 * Difficulty: Medium
 * Tags: tree, search
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
        // TODO: Implement optimized solution
        return 0;
    }
 * };
 */
#include <unordered_map>

using namespace std;

class Solution {
private:
    int dfs(TreeNode* node, long currentSum, int targetSum, unordered_map<long, int>& count) {
        if (!node) {
            return 0;
        }
        
        currentSum += node->val;
        int result = count[currentSum - targetSum];
        
        count[currentSum]++;
        result += dfs(node->left, currentSum, targetSum, count);
        result += dfs(node->right, currentSum, targetSum, count);
        count[currentSum]--;
        
        return result;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int> count;
        count[0] = 1;
        return dfs(root, 0, targetSum, count);
    }
};