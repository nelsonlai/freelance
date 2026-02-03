#include <vector>

using namespace std;

class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                int count = 0;
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] == 1 && grid[j][k] == 1) {
                        count++;
                    }
                }
                result += count * (count - 1) / 2;
            }
        }
        
        return result;
    }
};
