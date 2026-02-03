/*
 * Problem: Number of Distinct Islands
 * Difficulty: Medium
 * Tags: graph, hash, search
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& grid, int i, int j, vector<string>& shape, int startI, int startJ) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0) {
            return;
        }
        
        grid[i][j] = 0;
        shape.push_back(to_string(i - startI) + "," + to_string(j - startJ));
        
        dfs(grid, i + 1, j, shape, startI, startJ);
        dfs(grid, i - 1, j, shape, startI, startJ);
        dfs(grid, i, j + 1, shape, startI, startJ);
        dfs(grid, i, j - 1, shape, startI, startJ);
    }

public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        set<string> seen;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    vector<string> shape;
                    dfs(grid, i, j, shape, i, j);
                    string shapeStr = "";
                    for (string s : shape) {
                        shapeStr += s + ",";
                    }
                    seen.insert(shapeStr);
                }
            }
        }
        
        return seen.size();
    }
};