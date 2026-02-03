/*
 * Problem: Longest Word With All Prefixes
 * Difficulty: Medium
 * Tags: array, string, trie
 * 
 * Approach: Use Trie to check if all prefixes exist
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(n * m)
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
};

class Solution {
private:
    string result = "";
    
    void dfs(TrieNode* node, string path) {
        if (path.length() > result.length() || 
            (path.length() == result.length() && path < result)) {
            result = path;
        }
        
        vector<char> sorted;
        for (auto& p : node->children) {
            sorted.push_back(p.first);
        }
        sort(sorted.begin(), sorted.end());
        
        for (char c : sorted) {
            TrieNode* child = node->children[c];
            if (child->isEnd) {
                dfs(child, path + c);
            }
        }
    }
    
public:
    string longestWord(vector<string>& words) {
        TrieNode* root = new TrieNode();
        
        for (string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (node->children.find(c) == node->children.end()) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->isEnd = true;
        }
        
        dfs(root, "");
        return result;
    }
};