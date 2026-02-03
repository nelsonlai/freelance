#include <vector>

using namespace std;

class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        for (int m = 1; m <= n; m++) {
            for (int e = 1; e <= k; e++) {
                dp[m][e] = dp[m - 1][e - 1] + dp[m - 1][e] + 1;
                if (dp[m][e] >= n) {
                    return m;
                }
            }
        }
        return n;
    }
};
