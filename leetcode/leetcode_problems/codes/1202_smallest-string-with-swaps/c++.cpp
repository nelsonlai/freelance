/*
 * Problem: Smallest String With Swaps
 * Difficulty: Medium
 * Tags: array, string, graph, hash, sort, search
 * 
 * Approach: Union-Find to group connected indices, sort characters in each group
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for Union-Find and groups
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> parent;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) {
            parent[px] = py;
        }
    }
    
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.length();
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (auto& pair : pairs) {
            unite(pair[0], pair[1]);
        }
        
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < n; i++) {
            groups[find(i)].push_back(i);
        }
        
        for (auto& [root, indices] : groups) {
            vector<char> chars;
            for (int idx : indices) {
                chars.push_back(s[idx]);
            }
            sort(chars.begin(), chars.end());
            sort(indices.begin(), indices.end());
            for (int i = 0; i < indices.size(); i++) {
                s[indices[i]] = chars[i];
            }
        }
        
        return s;
    }
};