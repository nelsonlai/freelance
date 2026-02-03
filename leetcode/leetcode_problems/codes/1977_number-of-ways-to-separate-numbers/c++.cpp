/*
 * Problem: Number of Ways to Separate Numbers
 * Difficulty: Hard
 * Tags: array, string, dp
 * 
 * Approach: DP - dp[i][j] = ways to form valid sequence ending at position i with last number of length j
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n^2)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
    bool compare(string& num, int i, int j, int len, vector<vector<int>>& lcp) {
        if (i < len || j < len) {
            return false;
        }
        int common = lcp[i - len][j - len];
        if (common >= len) {
            return true;
        }
        return num[i - len + common] >= num[j - len + common];
    }
    
public:
    int numberOfCombinations(string num) {
        int n = num.length();
        
        if (num[0] == '0') {
            return 0;
        }
        
        // dp[i][j] = number of ways to form sequence ending at i with last number of length j
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
        dp[0][0] = 1;
        
        // Precompute LCP (longest common prefix) for string comparison
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (num[i] == num[j]) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                } else {
                    lcp[i][j] = 0;
                }
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (num[i - j] == '0') {
                    continue;
                }
                
                if (i - j == 0) {
                    dp[i][j] = 1;
                } else {
                    // Try all possible previous lengths
                    for (int k = 1; k <= min(j, i - j); k++) {
                        if (compare(num, i - j, i, k, lcp)) {
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD;
                        }
                    }
                    // Also try shorter previous number
                    if (i - j >= j) {
                        for (int k = 1; k < j; k++) {
                            dp[i][j] = (dp[i][j] + dp[i - j][k]) % MOD;
                        }
                    }
                }
            }
        }
        
        long long result = 0;
        for (int j = 0; j <= n; j++) {
            result = (result + dp[n][j]) % MOD;
        }
        
        return result;
    }
};
