/*
 * Problem: Linked List in Binary Tree
 * Difficulty: Medium
 * Tags: tree, search, linked_list
 * 
 * Approach: DFS - try matching from each node, recursively match linked list
 * Time Complexity: O(n * m) where n is tree nodes, m is list length
 * Space Complexity: O(h) for recursion stack
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
class Solution {
private:
    bool match(TreeNode* node, ListNode* listNode) {
        if (!listNode) {
            return true;
        }
        if (!node || node->val != listNode->val) {
            return false;
        }
        return match(node->left, listNode->next) || match(node->right, listNode->next);
    }
    
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!root) {
            return false;
        }
        
        if (match(root, head)) {
            return true;
        }
        
        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};
