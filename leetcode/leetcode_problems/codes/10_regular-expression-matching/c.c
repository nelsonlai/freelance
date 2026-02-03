/*
 * Problem: Regular Expression Matching
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isMatch(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);
    
    bool** dp = (bool**)malloc((m + 1) * sizeof(bool*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (bool*)calloc(n + 1, sizeof(bool));
    }
    
    dp[0][0] = true;
    
    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] || 
                           (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
            } else {
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }
    
    bool result = dp[m][n];
    
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}