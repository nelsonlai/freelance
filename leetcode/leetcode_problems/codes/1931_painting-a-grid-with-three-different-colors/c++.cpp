/*
 * Problem: Painting a Grid With Three Different Colors
 * Difficulty: Hard
 * Tags: dp, bitmask
 * 
 * Approach: DP with bitmask - track valid colorings for each column
 * Time Complexity: O(n * 3^m * m) where n is columns, m is rows
 * Space Complexity: O(3^m)
 */

#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    unordered_map<int, vector<int>> validColors;
    int m;
    
    int dp(int col, int prevCol, int n) {
        if (col == n) {
            return 1;
        }
        
        vector<int> valid = getValidColors(prevCol);
        long long result = 0;
        for (int color : valid) {
            result = (result + dp(col + 1, color, n)) % MOD;
        }
        return result;
    }
    
    vector<int> getValidColors(int prevCol) {
        if (validColors.find(prevCol) != validColors.end()) {
            return validColors[prevCol];
        }
        
        vector<int> colors;
        int maxMask = pow(3, m);
        
        for (int mask = 0; mask < maxMask; mask++) {
            bool valid = true;
            int temp = mask;
            int prev = prevCol;
            
            for (int i = 0; i < m; i++) {
                int curr = temp % 3;
                if (prevCol != -1) {
                    int prevDigit = prev % 3;
                    if (curr == prevDigit) {
                        valid = false;
                        break;
                    }
                }
                if (i > 0) {
                    int prevTemp = (temp / 3) % 3;
                    if (curr == prevTemp) {
                        valid = false;
                        break;
                    }
                }
                temp /= 3;
                if (prevCol != -1) {
                    prev /= 3;
                }
            }
            
            if (valid) {
                colors.push_back(mask);
            }
        }
        
        validColors[prevCol] = colors;
        return colors;
    }
    
public:
    int colorTheGrid(int m, int n) {
        this->m = m;
        return dp(0, -1, n);
    }
};