/*
 * Problem: Student Attendance Record II
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>

using namespace std;

class Solution {
public:
    int checkRecord(int n) {
        int MOD = 1000000007;
        
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 3;
        }
        
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        dp[0][0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int a = 0; a < 2; a++) {
                for (int l = 0; l < 3; l++) {
                    dp[i][a][0] = (dp[i][a][0] + dp[i-1][a][l]) % MOD;
                    if (a < 1) {
                        dp[i][a+1][0] = (dp[i][a+1][0] + dp[i-1][a][l]) % MOD;
                    }
                    if (l < 2) {
                        dp[i][a][l+1] = (dp[i][a][l+1] + dp[i-1][a][l]) % MOD;
                    }
                }
            }
        }
        
        int result = 0;
        for (int a = 0; a < 2; a++) {
            for (int l = 0; l < 3; l++) {
                result = (result + dp[n][a][l]) % MOD;
            }
        }
        
        return result;
    }
};