#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int MOD = 1000000007;
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        dp[0][0] = 1;
        
        for (int k = 0; k < group.size(); k++) {
            int g = group[k], p = profit[k];
            for (int i = n; i >= 0; i--) {
                for (int j = minProfit; j >= 0; j--) {
                    if (i + g <= n) {
                        dp[i + g][min(j + p, minProfit)] = 
                            (dp[i + g][min(j + p, minProfit)] + dp[i][j]) % MOD;
                    }
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i <= n; i++) {
            result = (result + dp[i][minProfit]) % MOD;
        }
        return result;
    }
};
