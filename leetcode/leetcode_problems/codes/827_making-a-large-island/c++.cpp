#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    int n;
    
    int dfs(vector<vector<int>>& grid, int r, int c, int idx) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) {
            return 0;
        }
        grid[r][c] = idx;
        return 1 + dfs(grid, r+1, c, idx) + dfs(grid, r-1, c, idx) + 
               dfs(grid, r, c+1, idx) + dfs(grid, r, c-1, idx);
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();
        int index = 2;
        unordered_map<int, int> area;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    area[index] = dfs(grid, i, j, index);
                    index++;
                }
            }
        }
        
        int result = 0;
        for (auto& entry : area) {
            result = max(result, entry.second);
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> seen;
                    vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
                    for (auto& dir : dirs) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            seen.insert(grid[ni][nj]);
                        }
                    }
                    int sum = 1;
                    for (int idx : seen) {
                        sum += area[idx];
                    }
                    result = max(result, sum);
                }
            }
        }
        return result;
    }
};
