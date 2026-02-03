/*
 * Problem: Number of Ways to Rearrange Sticks With K Sticks Visible
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: DP - dp[n][k] = ways to arrange n sticks with k visible
 * Time Complexity: O(n * k) where n, k are parameters
 * Space Complexity: O(n * k)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    const int MOD = 1000000007;
    
public:
    int rearrangeSticks(int n, int k) {
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                dp[i][j] = dp[i - 1][j - 1];
                dp[i][j] = (dp[i][j] + (i - 1) * dp[i - 1][j]) % MOD;
            }
        }
        
        return dp[n][k];
    }
};