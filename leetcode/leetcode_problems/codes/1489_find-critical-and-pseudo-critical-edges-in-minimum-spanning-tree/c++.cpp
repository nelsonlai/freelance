/*
 * Problem: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
 * Difficulty: Hard
 * Tags: array, tree, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        if (rank[px] < rank[py]) {
            swap(px, py);
        }
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
        return true;
    }
};

class Solution {
private:
    int mstWeight(int n, vector<vector<int>>& edgesWithIndex, int exclude, int include) {
        UnionFind uf(n);
        int weight = 0;
        int count = 0;
        
        if (include != -1) {
            vector<int>& edge = edgesWithIndex[include];
            if (uf.unite(edge[0], edge[1])) {
                weight += edge[2];
                count++;
            }
        }
        
        for (int i = 0; i < edgesWithIndex.size(); i++) {
            if (i == exclude || i == include) {
                continue;
            }
            vector<int>& edge = edgesWithIndex[i];
            if (uf.unite(edge[0], edge[1])) {
                weight += edge[2];
                count++;
                if (count == n - 1) {
                    break;
                }
            }
        }
        
        return count == n - 1 ? weight : INT_MAX;
    }
    
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<vector<int>> edgesWithIndex;
        for (int i = 0; i < m; i++) {
            edgesWithIndex.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }
        sort(edgesWithIndex.begin(), edgesWithIndex.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        int baseWeight = mstWeight(n, edgesWithIndex, -1, -1);
        vector<int> critical;
        vector<int> pseudoCritical;
        
        for (int i = 0; i < m; i++) {
            int weightWithout = mstWeight(n, edgesWithIndex, i, -1);
            if (weightWithout > baseWeight) {
                critical.push_back(edgesWithIndex[i][3]);
            } else {
                int weightWith = mstWeight(n, edgesWithIndex, -1, i);
                if (weightWith == baseWeight) {
                    pseudoCritical.push_back(edgesWithIndex[i][3]);
                }
            }
        }
        
        return {critical, pseudoCritical};
    }
};