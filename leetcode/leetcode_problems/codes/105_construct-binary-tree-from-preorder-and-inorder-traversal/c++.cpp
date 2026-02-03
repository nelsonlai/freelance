/*
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal
 * Difficulty: Medium
 * Tags: array, tree, hash
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
private:
    unordered_map<int, int> inorderMap;
    int preIndex = 0;
    
    TreeNode* build(vector<int>& preorder, int inStart, int inEnd) {
        if (inStart > inEnd) {
            return nullptr;
        }
        
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);
        int rootIndex = inorderMap[rootVal];
        
        root->left = build(preorder, inStart, rootIndex - 1);
        root->right = build(preorder, rootIndex + 1, inEnd);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        return build(preorder, 0, inorder.size() - 1);
    }
};