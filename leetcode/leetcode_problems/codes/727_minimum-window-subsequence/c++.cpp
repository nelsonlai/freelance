#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string minWindow(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        
        int minLen = INT_MAX;
        int start = -1;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
            
            if (dp[i][n] != -1) {
                int length = i - dp[i][n];
                if (length < minLen) {
                    minLen = length;
                    start = dp[i][n];
                }
            }
        }
        
        return start != -1 ? s1.substr(start, minLen) : "";
    }
};
