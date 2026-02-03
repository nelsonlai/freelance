/*
 * Problem: Redundant Connection II
 * Difficulty: Hard
 * Tags: array, tree, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
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
        parent[find(parent, x)] = find(parent, y);
    }

public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1, 0);
        vector<int> candidate1, candidate2;
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (parent[v] != 0) {
                candidate1 = {parent[v], v};
                candidate2 = edge;
            } else {
                parent[v] = u;
            }
        }
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        
        for (auto& edge : edges) {
            if (!candidate2.empty() && edge[0] == candidate2[0] && edge[1] == candidate2[1]) {
                continue;
            }
            int u = edge[0], v = edge[1];
            if (find(parent, u) == find(parent, v)) {
                return candidate1.empty() ? edge : candidate1;
            }
            unionSet(parent, u, v);
        }
        
        return candidate2;
    }
};