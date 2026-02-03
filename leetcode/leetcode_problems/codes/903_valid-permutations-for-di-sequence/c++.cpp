#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numPermsDISequence(string s) {
        int n = s.length();
        int MOD = 1000000007;
        vector<int> dp(n + 1, 1);
        
        for (int i = 0; i < n; i++) {
            vector<int> newDp(n + 1, 0);
            if (s[i] == 'I') {
                for (int j = 0; j < n - i; j++) {
                    for (int k = 0; k <= j; k++) {
                        newDp[j] = (newDp[j] + dp[k]) % MOD;
                    }
                }
            } else {
                for (int j = 0; j < n - i; j++) {
                    for (int k = j + 1; k <= n - i; k++) {
                        newDp[j] = (newDp[j] + dp[k]) % MOD;
                    }
                }
            }
            dp = newDp;
        }
        
        return dp[0];
    }
};
