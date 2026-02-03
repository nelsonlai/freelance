/*
 * Problem: Number of Connected Components in an Undirected Graph
 * Difficulty: Medium
 * Tags: array, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    void unionSet(vector<int>& parent, int x, int y) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px != py) {
            parent[px] = py;
        }
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (auto& edge : edges) {
            unionSet(parent, edge[0], edge[1]);
        }
        
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (find(parent, i) == i) {
                count++;
            }
        }
        
        return count;
    }
};