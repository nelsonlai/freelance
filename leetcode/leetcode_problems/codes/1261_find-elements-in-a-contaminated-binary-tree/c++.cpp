/*
 * Problem: Find Elements in a Contaminated Binary Tree
 * Difficulty: Medium
 * Tags: tree, hash, search
 * 
 * Approach: Recover tree values (left=2*val+1, right=2*val+2), store in set for O(1) lookup
 * Time Complexity: O(n) for init, O(1) for find
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

class FindElements {
public:
    unordered_set<int> values;
    
    FindElements(TreeNode* root) {
        recover(root, 0);
    }
    
    void recover(TreeNode* node, int val) {
        if (!node) {
            return;
        }
        node->val = val;
        values.insert(val);
        recover(node->left, 2 * val + 1);
        recover(node->right, 2 * val + 2);
    }
    
    bool find(int target) {
        return values.count(target);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
