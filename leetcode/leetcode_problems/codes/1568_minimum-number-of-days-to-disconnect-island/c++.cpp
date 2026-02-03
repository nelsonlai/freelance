/*
 * Problem: Minimum Number of Days to Disconnect Island
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c] || grid[r][c] == 0) {
            return;
        }
        visited[r][c] = true;
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : directions) {
            dfs(grid, r + dir[0], c + dir[1], visited, m, n);
        }
    }
    
    int countIslands(vector<vector<int>>& grid, int m, int n) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                    dfs(grid, i, j, visited, m, n);
                }
            }
        }
        
        return count;
    }
    
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int islands = countIslands(grid, m, n);
        if (islands != 1) {
            return 0;
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (countIslands(grid, m, n) != 1) {
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        
        return 2;
    }
};