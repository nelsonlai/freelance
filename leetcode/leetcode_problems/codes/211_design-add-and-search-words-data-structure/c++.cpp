/*
 * Problem: Design Add and Search Words Data Structure
 * Difficulty: Medium
 * Tags: string, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd;
    
    TrieNode() : isEnd(false) {}
};

class WordDictionary {
private:
    TrieNode* root;
    
    bool searchHelper(TrieNode* node, string& word, int index) {
        if (index == word.length()) {
            return node->isEnd;
        }
        
        char c = word[index];
        if (c == '.') {
            for (auto& pair : node->children) {
                if (searchHelper(pair.second, word, index + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            return searchHelper(node->children[c], word, index + 1);
        }
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        return searchHelper(root, word, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */