/*
 * Problem: Count Sub Islands
 * Difficulty: Medium
 * Tags: array, graph, search, DFS
 * 
 * Approach: DFS on grid2, check if all cells are also in grid1
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n) for recursion stack
 */

#include <vector>

using namespace std;

class Solution {
private:
    bool dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j) {
        int m = grid1.size();
        int n = grid1[0].size();
        
        if (i < 0 || i >= m || j < 0 || j >= n || grid2[i][j] == 0) {
            return true;
        }
        
        grid2[i][j] = 0;
        bool isSubIsland = grid1[i][j] == 1;
        
        isSubIsland = dfs(grid1, grid2, i + 1, j) && isSubIsland;
        isSubIsland = dfs(grid1, grid2, i - 1, j) && isSubIsland;
        isSubIsland = dfs(grid1, grid2, i, j + 1) && isSubIsland;
        isSubIsland = dfs(grid1, grid2, i, j - 1) && isSubIsland;
        
        return isSubIsland;
    }
    
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size();
        int n = grid1[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid2[i][j] == 1) {
                    if (dfs(grid1, grid2, i, j)) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};