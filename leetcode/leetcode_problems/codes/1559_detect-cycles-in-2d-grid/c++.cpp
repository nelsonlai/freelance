/*
 * Problem: Detect Cycles in 2D Grid
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
    bool dfs(vector<vector<char>>& grid, int r, int c, int pr, int pc, char ch, vector<vector<bool>>& visited, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != ch) {
            return false;
        }
        
        if (visited[r][c]) {
            return true;
        }
        
        visited[r][c] = true;
        
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : directions) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (nr != pr || nc != pc) {
                if (dfs(grid, nr, nc, r, c, ch, visited, m, n)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) {
                    if (dfs(grid, i, j, -1, -1, grid[i][j], visited, m, n)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};