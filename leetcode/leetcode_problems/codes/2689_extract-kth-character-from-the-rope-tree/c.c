/*
 * Problem: Extract Kth Character From The Rope Tree
 * Difficulty: Easy
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a rope tree node. */
struct RopeTreeNode {
    int len;
    char* val;
    struct RopeTreeNode* left;
    struct RopeTreeNode* right;
};

/// DO NOT MODIFY THE CODE ABOVE

char getKthCharacter(struct RopeTreeNode* root, int k){

}