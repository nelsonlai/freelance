/*
 * Problem: Bomb Enemy
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int rowHits = 0;
        vector<int> colHits(n, 0);
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0 || grid[i][j - 1] == 'W') {
                    rowHits = 0;
                    for (int k = j; k < n; k++) {
                        if (grid[i][k] == 'W') {
                            break;
                        }
                        if (grid[i][k] == 'E') {
                            rowHits++;
                        }
                    }
                }
                
                if (i == 0 || grid[i - 1][j] == 'W') {
                    colHits[j] = 0;
                    for (int k = i; k < m; k++) {
                        if (grid[k][j] == 'W') {
                            break;
                        }
                        if (grid[k][j] == 'E') {
                            colHits[j]++;
                        }
                    }
                }
                
                if (grid[i][j] == '0') {
                    result = max(result, rowHits + colHits[j]);
                }
            }
        }
        
        return result;
    }
};