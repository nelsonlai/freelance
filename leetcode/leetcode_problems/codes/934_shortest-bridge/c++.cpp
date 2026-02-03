/*
 * Problem: Shortest Bridge
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: DFS to find first island, then BFS to find shortest path to second island
 * Time Complexity: O(n * m) where n and m are dimensions
 * Space Complexity: O(n * m) for queue and visited set
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    void dfs(vector<vector<int>>& grid, int i, int j, vector<pair<int, int>>& island, int n) {
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) {
            return;
        }
        grid[i][j] = 2;
        island.push_back({i, j});
        for (auto& dir : directions) {
            dfs(grid, i + dir[0], j + dir[1], island, n);
        }
    }
    
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> island;
        
        // Find first island using DFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, island, n);
                    break;
                }
            }
            if (!island.empty()) break;
        }
        
        // BFS to find shortest path to second island
        queue<vector<int>> q;
        unordered_set<string> visited;
        
        for (auto& cell : island) {
            q.push({cell.first, cell.second, 0});
            visited.insert(to_string(cell.first) + "," + to_string(cell.second));
        }
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int i = curr[0], j = curr[1], dist = curr[2];
            
            for (auto& dir : directions) {
                int ni = i + dir[0], nj = j + dir[1];
                string key = to_string(ni) + "," + to_string(nj);
                
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && visited.find(key) == visited.end()) {
                    if (grid[ni][nj] == 1) {
                        return dist;
                    }
                    visited.insert(key);
                    q.push({ni, nj, dist + 1});
                }
            }
        }
        
        return -1;
    }
};