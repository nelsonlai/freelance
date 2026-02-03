/*
 * Problem: Walls and Gates
 * Difficulty: Medium
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
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) {
            return;
        }
        
        int m = rooms.size();
        int n = rooms[0].size();
        queue<pair<int, int>> q;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int r = row + dir[0];
                int c = col + dir[1];
                if (r >= 0 && r < m && c >= 0 && c < n && rooms[r][c] == INT_MAX) {
                    rooms[r][c] = rooms[row][col] + 1;
                    q.push({r, c});
                }
            }
        }
    }
};