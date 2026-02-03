/*
 * Problem: Check If Two Expression Trees are Equivalent
 * Difficulty: Medium
 * Tags: tree, hash, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <unordered_map>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    unordered_map<char, int> countVars(Node* node) {
        unordered_map<char, int> count;
        if (!node) {
            return count;
        }
        
        if (node->val != '+' && node->val != '-' && node->val != '*' && node->val != '/') {
            count[node->val]++;
            return count;
        }
        
        auto leftCount = countVars(node->left);
        auto rightCount = countVars(node->right);
        
        for (auto& [ch, cnt] : leftCount) {
            count[ch] += cnt;
        }
        for (auto& [ch, cnt] : rightCount) {
            count[ch] += cnt;
        }
        
        return count;
    }
    
public:
    bool checkEquivalence(Node* root1, Node* root2) {
        return countVars(root1) == countVars(root2);
    }
};