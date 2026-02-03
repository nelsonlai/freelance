/*
 * Problem: Shortest Distance from All Buildings
 * Difficulty: Hard
 * Tags: array, tree, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
private:
    bool bfs(vector<vector<int>>& grid, int startI, int startJ, 
            vector<vector<int>>& distance, vector<vector<int>>& reach, int totalBuildings) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<vector<int>> q;
        q.push({startI, startJ, 0});
        visited[startI][startJ] = true;
        int count = 1;
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int i = curr[0], j = curr[1], dist = curr[2];
            
            for (auto& dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    if (grid[ni][nj] == 0) {
                        distance[ni][nj] += dist + 1;
                        reach[ni][nj]++;
                        q.push({ni, nj, dist + 1});
                    } else if (grid[ni][nj] == 1) {
                        count++;
                    }
                }
            }
        }
        
        return count == totalBuildings;
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int buildings = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    buildings++;
                }
            }
        }
        
        vector<vector<int>> distance(m, vector<int>(n, 0));
        vector<vector<int>> reach(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (!bfs(grid, i, j, distance, reach, buildings)) {
                        return -1;
                    }
                }
            }
        }
        
        int minDistance = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && reach[i][j] == buildings) {
                    minDistance = min(minDistance, distance[i][j]);
                }
            }
        }
        
        return minDistance == INT_MAX ? -1 : minDistance;
    }
};