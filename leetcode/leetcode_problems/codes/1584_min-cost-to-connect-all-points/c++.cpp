/*
 * Problem: Min Cost to Connect All Points
 * Difficulty: Medium
 * Tags: array, tree, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
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
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> edges;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.push_back({cost, i, j});
            }
        }
        
        sort(edges.begin(), edges.end());
        
        vector<int> parent(n);
        vector<int> rank(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        int result = 0;
        int count = 0;
        
        for (auto& edge : edges) {
            if (unite(parent, rank, edge[1], edge[2])) {
                result += edge[0];
                count++;
                if (count == n - 1) {
                    break;
                }
            }
        }
        
        return result;
    }
};