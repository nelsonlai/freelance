/*
 * Problem: Delete Duplicate Folders in System
 * Difficulty: Hard
 * Tags: array, string, hash, trie, tree serialization
 * 
 * Approach: Build trie, serialize subtrees, mark duplicates, collect non-duplicate paths
 * Time Complexity: O(n * m) where n is paths, m is avg depth
 * Space Complexity: O(n * m)
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

struct TrieNode {
    map<string, TrieNode*> children;
    int count = 0;
};

class Solution {
private:
    string serialize(TrieNode* node, unordered_map<string, int>& serialMap) {
        if (node->children.empty()) {
            return "";
        }
        
        vector<string> parts;
        for (auto& [key, child] : node->children) {
            string childSerial = serialize(child, serialMap);
            parts.push_back(key + "(" + childSerial + ")");
        }
        
        string serial;
        for (size_t i = 0; i < parts.size(); i++) {
            if (i > 0) serial += ",";
            serial += parts[i];
        }
        
        serialMap[serial]++;
        return serial;
    }
    
    string markDuplicates(TrieNode* node, unordered_map<string, int>& serialMap) {
        if (node->children.empty()) {
            return "";
        }
        
        vector<string> parts;
        for (auto& [key, child] : node->children) {
            string childSerial = markDuplicates(child, serialMap);
            parts.push_back(key + "(" + childSerial + ")");
        }
        
        string serial;
        for (size_t i = 0; i < parts.size(); i++) {
            if (i > 0) serial += ",";
            serial += parts[i];
        }
        
        if (serialMap[serial] > 1) {
            node->count = -1;
        }
        return serial;
    }
    
    void collect(TrieNode* node, vector<string>& path, vector<vector<string>>& result) {
        if (node->count == -1) {
            return;
        }
        
        if (!path.empty()) {
            result.push_back(path);
        }
        
        for (auto& [folder, child] : node->children) {
            if (child->count != -1) {
                path.push_back(folder);
                collect(child, path, result);
                path.pop_back();
            }
        }
    }
    
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        TrieNode* root = new TrieNode();
        
        sort(paths.begin(), paths.end());
        
        for (auto& path : paths) {
            TrieNode* node = root;
            for (string& folder : path) {
                if (node->children.find(folder) == node->children.end()) {
                    node->children[folder] = new TrieNode();
                }
                node = node->children[folder];
            }
        }
        
        unordered_map<string, int> serialMap;
        serialize(root, serialMap);
        markDuplicates(root, serialMap);
        
        vector<vector<string>> result;
        vector<string> path;
        collect(root, path, result);
        
        return result;
    }
};