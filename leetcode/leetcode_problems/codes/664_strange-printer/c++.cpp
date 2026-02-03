/*
 * Problem: Strange Printer
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int strangePrinter(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i < n - length + 1; i++) {
                int j = i + length - 1;
                dp[i][j] = dp[i][j-1] + 1;
                
                for (int k = i; k < j; k++) {
                    if (s[k] == s[j]) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + (k + 1 <= j - 1 ? dp[k+1][j-1] : 0));
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
};