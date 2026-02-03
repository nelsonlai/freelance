/*
 * Problem: Encode String with Shortest Length
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string encode(string s) {
        int n = s.length();
        vector<vector<string>> dp(n, vector<string>(n));
        
        for (int length = 1; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                string substr = s.substr(i, length);
                dp[i][j] = substr;
                
                if (length > 4) {
                    for (int k = i; k < j; k++) {
                        if (dp[i][k].length() + dp[k+1][j].length() < dp[i][j].length()) {
                            dp[i][j] = dp[i][k] + dp[k+1][j];
                        }
                    }
                    
                    for (int k = 1; k <= length / 2; k++) {
                        if (length % k == 0) {
                            string pattern = s.substr(i, k);
                            string repeated = "";
                            for (int rep = 0; rep < length / k; rep++) {
                                repeated += pattern;
                            }
                            if (repeated == substr) {
                                string encoded = to_string(length / k) + "[" + dp[i][i+k-1] + "]";
                                if (encoded.length() < dp[i][j].length()) {
                                    dp[i][j] = encoded;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
};