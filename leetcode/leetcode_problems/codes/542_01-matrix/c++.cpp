/*
 * Problem: 01 Matrix
 * Difficulty: Medium
 * Tags: array, dp, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        queue<vector<int>> q;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                } else {
                    mat[i][j] = INT_MAX;
                }
            }
        }
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int x = curr[0], y = curr[1];
            
            for (auto& dir : directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && mat[nx][ny] > mat[x][y] + 1) {
                    mat[nx][ny] = mat[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        
        return mat;
    }
};