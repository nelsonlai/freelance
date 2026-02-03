/*
 * Problem: Distinct Subsequences II
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: Dynamic programming - track distinct subsequences ending at each position
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1) using constant space for last occurrence tracking
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        int MOD = 1000000007;
        int n = s.length();
        vector<long> dp(n + 1, 0);
        vector<int> lastOccurrence(26, -1);
        
        dp[0] = 1; // Empty subsequence
        
        for (int i = 1; i <= n; i++) {
            char c = s[i - 1];
            dp[i] = (2 * dp[i - 1]) % MOD;
            if (lastOccurrence[c - 'a'] != -1) {
                dp[i] = (dp[i] - dp[lastOccurrence[c - 'a'] - 1] + MOD) % MOD;
            }
            lastOccurrence[c - 'a'] = i;
        }
        
        return (int) ((dp[n] - 1) % MOD); // Subtract empty subsequence
    }
};