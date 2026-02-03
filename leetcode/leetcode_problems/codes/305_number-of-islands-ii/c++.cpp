/*
 * Problem: Number of Islands II
 * Difficulty: Hard
 * Tags: array, graph, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;
    int count = 0;
    
    string find(string x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unionIslands(string x, string y) {
        string px = find(x);
        string py = find(y);
        
        if (px == py) {
            return;
        }
        
        if (rank[px] < rank[py]) {
            swap(px, py);
        }
        
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
        count--;
    }

public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> result;
        
        for (auto& pos : positions) {
            int r = pos[0];
            int c = pos[1];
            string key = to_string(r) + "," + to_string(c);
            
            if (parent.find(key) != parent.end()) {
                result.push_back(count);
                continue;
            }
            
            parent[key] = key;
            rank[key] = 0;
            count++;
            
            vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for (auto& dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                string neighbor = to_string(nr) + "," + to_string(nc);
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && parent.find(neighbor) != parent.end()) {
                    unionIslands(key, neighbor);
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};