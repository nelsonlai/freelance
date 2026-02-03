/*
 * Problem: Number of Ways to Wear Different Hats to Each Other
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP with bitmask - dp[mask][hat] = ways to assign hats to people in mask
 * Time Complexity: O(n * 2^n * m) where n is people, m is hats
 * Space Complexity: O(2^n * m)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        int MOD = 1000000007;
        int n = hats.size();
        vector<vector<int>> hatToPeople(41);
        
        for (int person = 0; person < n; person++) {
            for (int hat : hats[person]) {
                hatToPeople[hat].push_back(person);
            }
        }
        
        vector<long long> dp(1 << n, 0);
        dp[0] = 1;
        
        for (int hat = 1; hat <= 40; hat++) {
            vector<long long> newDp = dp;
            for (int person : hatToPeople[hat]) {
                for (int mask = 0; mask < (1 << n); mask++) {
                    if (mask & (1 << person)) {
                        newDp[mask] = (newDp[mask] + dp[mask ^ (1 << person)]) % MOD;
                    }
                }
            }
            dp = newDp;
        }
        
        return (int) dp[(1 << n) - 1];
    }
};