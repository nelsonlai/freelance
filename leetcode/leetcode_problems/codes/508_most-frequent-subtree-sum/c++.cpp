/*
 * Problem: Most Frequent Subtree Sum
 * Difficulty: Medium
 * Tags: tree, hash, search
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
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<int, int> count;
    
    int dfs(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftSum = dfs(node->left);
        int rightSum = dfs(node->right);
        int total = node->val + leftSum + rightSum;
        count[total]++;
        
        return total;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        dfs(root);
        
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