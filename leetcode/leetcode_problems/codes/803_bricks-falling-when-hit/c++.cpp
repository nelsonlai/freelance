#include <vector>

using namespace std;

class Solution {
private:
    int m, n;
    
    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1) {
            return 0;
        }
        grid[i][j] = 2;
        return 1 + dfs(grid, i+1, j) + dfs(grid, i-1, j) + 
               dfs(grid, i, j+1) + dfs(grid, i, j-1);
    }
    
    bool isConnected(vector<vector<int>>& grid, int i, int j) {
        vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        for (auto& dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 2) {
                return true;
            }
        }
        return false;
    }

public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        m = grid.size();
        n = grid[0].size();
        
        for (auto& hit : hits) {
            if (grid[hit[0]][hit[1]] == 1) {
                grid[hit[0]][hit[1]] = 0;
            }
        }
        
        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);
        }
        
        vector<int> result(hits.size());
        for (int k = hits.size() - 1; k >= 0; k--) {
            int i = hits[k][0], j = hits[k][1];
            grid[i][j] = 1;
            if (i == 0 || isConnected(grid, i, j)) {
                int count = dfs(grid, i, j) - 1;
                result[k] = count;
            }
        }
        return result;
    }
};
