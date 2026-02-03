#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 0) {
                for (int j = 0; j < n; j++) {
                    grid[i][j] = 1 - grid[i][j];
                }
            }
        }
        
        int result = m * (1 << (n - 1));
        
        for (int j = 1; j < n; j++) {
            int count = 0;
            for (int i = 0; i < m; i++) {
                count += grid[i][j];
            }
            result += max(count, m - count) * (1 << (n - 1 - j));
        }
        
        return result;
    }
};
