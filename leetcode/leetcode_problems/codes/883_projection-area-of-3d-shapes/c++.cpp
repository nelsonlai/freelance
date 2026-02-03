#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            int maxRow = 0, maxCol = 0;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    result++;
                }
                maxRow = max(maxRow, grid[i][j]);
                maxCol = max(maxCol, grid[j][i]);
            }
            result += maxRow + maxCol;
        }
        
        return result;
    }
};
