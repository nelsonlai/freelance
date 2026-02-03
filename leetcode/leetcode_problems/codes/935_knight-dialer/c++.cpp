/*
 * Problem: Knight Dialer
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming - track number of ways to reach each digit
 * Time Complexity: O(n) where n is number of hops
 * Space Complexity: O(1) using constant space for DP
 */

#include <vector>

using namespace std;

class Solution {
public:
    int knightDialer(int n) {
        if (n == 1) return 10;
        
        vector<vector<int>> moves = {
            {4, 6}, {6, 8}, {7, 9}, {4, 8},
            {0, 3, 9}, {}, {0, 1, 7},
            {2, 6}, {1, 3}, {2, 4}
        };
        
        int MOD = 1000000007;
        vector<long> dp(10, 1);
        
        for (int step = 1; step < n; step++) {
            vector<long> newDp(10, 0);
            for (int digit = 0; digit < 10; digit++) {
                for (int nextDigit : moves[digit]) {
                    newDp[nextDigit] = (newDp[nextDigit] + dp[digit]) % MOD;
                }
            }
            dp = newDp;
        }
        
        long result = 0;
        for (long count : dp) {
            result = (result + count) % MOD;
        }
        return (int) result;
    }
};