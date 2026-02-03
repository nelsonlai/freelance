#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    result += 2;
                    if (i > 0) {
                        result += abs(grid[i][j] - grid[i - 1][j]);
                    } else {
                        result += grid[i][j];
                    }
                    if (i < n - 1) {
                        result += abs(grid[i][j] - grid[i + 1][j]);
                    } else {
                        result += grid[i][j];
                    }
                    if (j > 0) {
                        result += abs(grid[i][j] - grid[i][j - 1]);
                    } else {
                        result += grid[i][j];
                    }
                    if (j < n - 1) {
                        result += abs(grid[i][j] - grid[i][j + 1]);
                    } else {
                        result += grid[i][j];
                    }
                }
            }
        }
        return result;
    }
};
