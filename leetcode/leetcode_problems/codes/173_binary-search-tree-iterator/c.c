/*
 * Problem: Binary Search Tree Iterator
 * Difficulty: Medium
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
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



typedef struct {
    
} BSTIterator;


BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    
}

int bSTIteratorNext(BSTIterator* obj) {
    
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    
}

void bSTIteratorFree(BSTIterator* obj) {
    
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 
 * bool param_2 = bSTIteratorHasNext(obj);
 
 * bSTIteratorFree(obj);
*/