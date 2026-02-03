/*
 * Problem: Remove Max Number of Edges to Keep Graph Fully Traversable
 * Difficulty: Hard
 * Tags: array, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    bool unite(vector<int>& parent, vector<int>& rank, int x, int y) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px == py) {
            return false;
        }
        if (rank[px] < rank[py]) {
            swap(px, py);
        }
        parent[py] = px;
        rank[px] += rank[py];
        return true;
    }
    
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<int>> type3Edges, type1Edges, type2Edges;
        
        for (auto& edge : edges) {
            int t = edge[0];
            int u = edge[1] - 1;
            int v = edge[2] - 1;
            if (t == 3) {
                type3Edges.push_back({u, v});
            } else if (t == 1) {
                type1Edges.push_back({u, v});
            } else {
                type2Edges.push_back({u, v});
            }
        }
        
        vector<int> parent(n);
        vector<int> rank(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        int used = 0;
        for (auto& edge : type3Edges) {
            if (unite(parent, rank, edge[0], edge[1])) {
                used++;
            }
        }
        
        vector<int> parent1 = parent, rank1 = rank;
        vector<int> parent2 = parent, rank2 = rank;
        
        for (auto& edge : type1Edges) {
            if (unite(parent1, rank1, edge[0], edge[1])) {
                used++;
            }
        }
        
        for (auto& edge : type2Edges) {
            if (unite(parent2, rank2, edge[0], edge[1])) {
                used++;
            }
        }
        
        if (rank1[find(parent1, 0)] != n || rank2[find(parent2, 0)] != n) {
            return -1;
        }
        
        return edges.size() - used;
    }
};