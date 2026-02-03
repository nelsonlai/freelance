/*
 * Problem: Coin Path
 * Difficulty: Hard
 * Tags: array, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size();
        if (coins[n-1] == -1) {
            return {};
        }
        
        vector<long long> dp(n, LLONG_MAX);
        vector<int> next(n, -1);
        dp[n-1] = coins[n-1];
        
        for (int i = n - 2; i >= 0; i--) {
            if (coins[i] == -1) {
                continue;
            }
            
            for (int j = i + 1; j < min(i + maxJump + 1, n); j++) {
                if (dp[j] != LLONG_MAX && dp[j] + coins[i] < dp[i]) {
                    dp[i] = dp[j] + coins[i];
                    next[i] = j;
                }
            }
        }
        
        if (dp[0] == LLONG_MAX) {
            return {};
        }
        
        vector<int> result;
        int i = 0;
        while (i != -1) {
            result.push_back(i + 1);
            i = next[i];
        }
        
        return result;
    }
};