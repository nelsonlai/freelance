#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> rowMax(m, 0);
        vector<int> colMax(n, 0);
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowMax[i] = max(rowMax[i], grid[i][j]);
                colMax[j] = max(colMax[j], grid[i][j]);
            }
        }
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result += min(rowMax[i], colMax[j]) - grid[i][j];
            }
        }
        return result;
    }
};
