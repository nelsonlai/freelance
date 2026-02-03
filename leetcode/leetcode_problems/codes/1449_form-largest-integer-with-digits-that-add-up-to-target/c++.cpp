/*
 * Problem: Form Largest Integer With Digits That Add up to Target
 * Difficulty: Hard
 * Tags: array, string, dp
 * 
 * Approach: DP - dp[i] = largest string for cost i, try all digits
 * Time Complexity: O(target * 9)
 * Space Complexity: O(target)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<string> dp(target + 1, "");
        
        for (int i = 1; i <= target; i++) {
            for (int digit = 9; digit >= 1; digit--) {
                int c = cost[digit - 1];
                if (i >= c && (i == c || !dp[i - c].empty())) {
                    string candidate = to_string(digit) + dp[i - c];
                    if (candidate.length() > dp[i].length() || 
                        (candidate.length() == dp[i].length() && candidate > dp[i])) {
                        dp[i] = candidate;
                    }
                }
            }
        }
        
        return dp[target].empty() ? "0" : dp[target];
    }
};