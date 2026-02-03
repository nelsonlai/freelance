/*
 * Problem: Last Day Where You Can Still Cross
 * Difficulty: Hard
 * Tags: array, graph, search, binary search, BFS/DFS
 * 
 * Approach: Binary search on day, check if path exists using BFS
 * Time Complexity: O(row * col * log(len(cells)))
 * Space Complexity: O(row * col)
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    bool canCross(int row, int col, vector<vector<int>>& cells, int day) {
        vector<vector<int>> grid(row, vector<int>(col, 0));
        for (int i = 0; i < day; i++) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r][c] = 1;
        }
        
        queue<pair<int, int>> q;
        for (int c = 0; c < col; c++) {
            if (grid[0][c] == 0) {
                q.push({0, c});
                grid[0][c] = 1;
            }
        }
        
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (r == row - 1) {
                return true;
            }
            
            for (auto& dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
        
        return false;
    }
    
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int left = 0, right = cells.size();
        int result = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (canCross(row, col, cells, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};