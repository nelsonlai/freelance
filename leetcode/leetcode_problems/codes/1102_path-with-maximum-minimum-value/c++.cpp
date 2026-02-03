/*
 * Problem: Path With Maximum Minimum Value
 * Difficulty: Medium
 * Tags: array, graph, search, queue, heap
 * 
 * Approach: Use max-heap to always explore highest value paths
 * Time Complexity: O(m * n * log(m * n))
 * Space Complexity: O(m * n) for visited
 */
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        priority_queue<vector<int>> heap;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        heap.push({grid[0][0], 0, 0});
        int minVal = grid[0][0];
        
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int val = curr[0];
            int r = curr[1];
            int c = curr[2];
            
            minVal = min(minVal, val);
            
            if (r == m - 1 && c == n - 1) {
                return minVal;
            }
            
            if (visited[r][c]) {
                continue;
            }
            visited[r][c] = true;
            
            for (auto& dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    heap.push({grid[nr][nc], nr, nc});
                }
            }
        }
        
        return minVal;
    }
};