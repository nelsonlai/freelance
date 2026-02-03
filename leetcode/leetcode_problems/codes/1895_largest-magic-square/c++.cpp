/*
 * Problem: Largest Magic Square
 * Difficulty: Medium
 * Tags: array, prefix sum
 * 
 * Approach: Try all sizes, use prefix sum to check if magic square
 * Time Complexity: O(m * n * min(m,n)^2) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> rowSum(m, vector<int>(n + 1, 0));
        vector<vector<int>> colSum(n, vector<int>(m + 1, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowSum[i][j + 1] = rowSum[i][j] + grid[i][j];
                colSum[j][i + 1] = colSum[j][i] + grid[i][j];
            }
        }
        
        int result = 1;
        
        for (int size = 2; size <= min(m, n); size++) {
            for (int i = 0; i <= m - size; i++) {
                for (int j = 0; j <= n - size; j++) {
                    int target = rowSum[i][j + size] - rowSum[i][j];
                    bool valid = true;
                    
                    for (int r = i; r < i + size; r++) {
                        if (rowSum[r][j + size] - rowSum[r][j] != target) {
                            valid = false;
                            break;
                        }
                    }
                    
                    if (!valid) continue;
                    
                    for (int c = j; c < j + size; c++) {
                        if (colSum[c][i + size] - colSum[c][i] != target) {
                            valid = false;
                            break;
                        }
                    }
                    
                    if (!valid) continue;
                    
                    int diag1 = 0, diag2 = 0;
                    for (int k = 0; k < size; k++) {
                        diag1 += grid[i + k][j + k];
                        diag2 += grid[i + k][j + size - 1 - k];
                    }
                    
                    if (diag1 == target && diag2 == target) {
                        result = size;
                    }
                }
            }
        }
        
        return result;
    }
};