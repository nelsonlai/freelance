/*
 * Problem: Maximum Genetic Difference Query
 * Difficulty: Hard
 * Tags: array, tree, hash, search, trie, DFS
 * 
 * Approach: Build tree, use Trie to find max XOR for each query path
 * Time Complexity: O(n * 18 + q * 18) where n is nodes, q is queries, 18 is bits
 * Space Complexity: O(n * 18)
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TrieNode {
    int count = 0;
    TrieNode* children[2] = {nullptr, nullptr};
};

class Solution {
private:
    void add(TrieNode* root, int num) {
        TrieNode* node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }
    
    void remove(TrieNode* root, int num) {
        TrieNode* node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            node = node->children[bit];
            node->count--;
        }
    }
    
    int query(TrieNode* root, int num) {
        TrieNode* node = root;
        int res = 0;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int target = 1 - bit;
            if (node->children[target] && node->children[target]->count > 0) {
                res |= (1 << i);
                node = node->children[target];
            } else {
                node = node->children[bit];
            }
        }
        return res;
    }
    
    void dfs(int node, vector<vector<int>>& graph, 
             unordered_map<int, vector<pair<int, int>>>& queryMap,
             TrieNode* trie, vector<int>& result) {
        add(trie, node);
        
        if (queryMap.find(node) != queryMap.end()) {
            for (auto& [val, idx] : queryMap[node]) {
                result[idx] = query(trie, val);
            }
        }
        
        for (int child : graph[node]) {
            dfs(child, graph, queryMap, trie, result);
        }
        
        remove(trie, node);
    }
    
public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        int n = parents.size();
        int rootIdx = -1;
        vector<vector<int>> graph(n);
        
        for (int i = 0; i < n; i++) {
            if (parents[i] == -1) {
                rootIdx = i;
            } else {
                graph[parents[i]].push_back(i);
            }
        }
        
        unordered_map<int, vector<pair<int, int>>> queryMap;
        for (int i = 0; i < queries.size(); i++) {
            int node = queries[i][0];
            int val = queries[i][1];
            queryMap[node].push_back({val, i});
        }
        
        vector<int> result(queries.size());
        TrieNode* trie = new TrieNode();
        
        dfs(rootIdx, graph, queryMap, trie, result);
        
        return result;
    }
};