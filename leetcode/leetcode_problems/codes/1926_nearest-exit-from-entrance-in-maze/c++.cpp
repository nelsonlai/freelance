/*
 * Problem: Nearest Exit from Entrance in Maze
 * Difficulty: Medium
 * Tags: array, graph, search, BFS
 * 
 * Approach: BFS from entrance, find nearest border cell
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();
        queue<vector<int>> q;
        q.push({entrance[0], entrance[1], 0});
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[entrance[0]][entrance[1]] = true;
        
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int i = curr[0], j = curr[1], steps = curr[2];
            
            if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && 
                (i != entrance[0] || j != entrance[1])) {
                return steps;
            }
            
            for (auto& dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && 
                    maze[ni][nj] == '.' && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    q.push({ni, nj, steps + 1});
                }
            }
        }
        
        return -1;
    }
};