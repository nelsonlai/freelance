/*
 * Problem: Maximum Vacation Days
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();
        int k = days[0].size();
        
        vector<vector<int>> dp(k, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            if (i == 0 || flights[0][i] == 1) {
                dp[0][i] = days[i][0];
            }
        }
        
        for (int week = 1; week < k; week++) {
            for (int city = 0; city < n; city++) {
                for (int prevCity = 0; prevCity < n; prevCity++) {
                    if (dp[week-1][prevCity] != -1) {
                        if (prevCity == city || flights[prevCity][city] == 1) {
                            dp[week][city] = max(dp[week][city], 
                                                dp[week-1][prevCity] + days[city][week]);
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            result = max(result, dp[k-1][i]);
        }
        
        return result;
    }
};