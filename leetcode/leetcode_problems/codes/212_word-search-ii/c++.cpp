/*
 * Problem: Word Search II
 * Difficulty: Hard
 * Tags: array, string, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    string word;
    
    TrieNode() : word("") {}
};

class Solution {
private:
    vector<string> result;
    
    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, int m, int n) {
        char c = board[i][j];
        TrieNode* currNode = node->children[c];
        
        if (!currNode->word.empty()) {
            result.push_back(currNode->word);
            currNode->word = "";
        }
        
        board[i][j] = '#';
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& dir : dirs) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && currNode->children.find(board[ni][nj]) != currNode->children.end()) {
                dfs(board, ni, nj, currNode, m, n);
            }
        }
        board[i][j] = c;
        
        if (currNode->children.empty()) {
            node->children.erase(c);
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (string word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (node->children.find(c) == node->children.end()) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->word = word;
        }
        
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (root->children.find(board[i][j]) != root->children.end()) {
                    dfs(board, i, j, root, m, n);
                }
            }
        }
        
        return result;
    }
};