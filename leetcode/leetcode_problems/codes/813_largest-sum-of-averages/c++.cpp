#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0.0));
        for (int i = 1; i <= n; i++) {
            dp[i][1] = prefix[i] / i;
        }
        
        for (int j = 2; j <= k; j++) {
            for (int i = j; i <= n; i++) {
                for (int p = j - 1; p < i; p++) {
                    dp[i][j] = max(dp[i][j], dp[p][j-1] + (prefix[i] - prefix[p]) / (i - p));
                }
            }
        }
        
        return dp[n][k];
    }
};
