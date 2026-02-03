/*
 * Problem: Design Search Autocomplete System
 * Difficulty: Hard
 * Tags: array, string, hash, sort, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    unordered_map<string, int> sentences;
};

class AutocompleteSystem {
private:
    TrieNode* root;
    TrieNode* currentNode;
    string currentSentence;
    
    void addSentence(string sentence, int time) {
        TrieNode* node = root;
        for (char c : sentence) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->sentences[sentence] += time;
        }
    }

public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        currentNode = root;
        currentSentence = "";
        
        for (int i = 0; i < sentences.size(); i++) {
            addSentence(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            addSentence(currentSentence, 1);
            currentSentence = "";
            currentNode = root;
            return {};
        }
        
        currentSentence += c;
        if (currentNode && currentNode->children.find(c) != currentNode->children.end()) {
            currentNode = currentNode->children[c];
        } else {
            currentNode = nullptr;
            return {};
        }
        
        vector<pair<string, int>> candidates;
        for (auto& entry : currentNode->sentences) {
            candidates.push_back(entry);
        }
        
        sort(candidates.begin(), candidates.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
        
        vector<string> result;
        for (int i = 0; i < min(3, (int)candidates.size()); i++) {
            result.push_back(candidates[i].first);
        }
        
        return result;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */