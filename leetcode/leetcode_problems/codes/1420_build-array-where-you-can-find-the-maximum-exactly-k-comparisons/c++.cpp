/*
 * Problem: Build Array Where You Can Find The Maximum Exactly K Comparisons
 * Difficulty: Hard
 * Tags: array, dp, search
 * 
 * Approach: DP - dp[i][j][l] = ways to build array of length i, max value j, k comparisons l
 * Time Complexity: O(n * m * k)
 * Space Complexity: O(n * m * k)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        int MOD = 1000000007;
        
        if (k == 0) {
            return 0;
        }
        
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m + 1, vector<long long>(k + 1, 0)));
        
        for (int j = 1; j <= m; j++) {
            dp[1][j][1] = 1;
        }
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int l = 1; l <= min(i, k); l++) {
                    dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j][l] * j) % MOD;
                    for (int prevMax = 1; prevMax < j; prevMax++) {
                        dp[i][j][l] = (dp[i][j][l] + dp[i - 1][prevMax][l - 1]) % MOD;
                    }
                }
            }
        }
        
        long long result = 0;
        for (int j = 1; j <= m; j++) {
            result = (result + dp[n][j][k]) % MOD;
        }
        
        return (int) result;
    }
};