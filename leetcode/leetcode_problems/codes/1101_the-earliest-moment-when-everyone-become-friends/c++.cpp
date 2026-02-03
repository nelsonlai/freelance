/*
 * Problem: The Earliest Moment When Everyone Become Friends
 * Difficulty: Medium
 * Tags: array, graph, sort
 * 
 * Approach: Union-Find - sort logs by time, union friends until all connected
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for Union-Find
 */
#include <vector>
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
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        parent[px] = py;
        return true;
    }
    
    int earliestAcq(vector<vector<int>>& logs, int n) {
        sort(logs.begin(), logs.end());
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        int components = n;
        for (auto& log : logs) {
            int time = log[0];
            int x = log[1];
            int y = log[2];
            if (unite(x, y)) {
                components--;
                if (components == 1) {
                    return time;
                }
            }
        }
        
        return -1;
    }
};