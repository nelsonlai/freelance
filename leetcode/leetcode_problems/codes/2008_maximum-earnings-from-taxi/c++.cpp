/*
 * Problem: Maximum Earnings From Taxi
 * Difficulty: Medium
 * Tags: array, dp, hash, sort, search
 * 
 * Approach: DP - sort rides by end time, use binary search to find previous compatible ride
 * Time Complexity: O(n log n) where n is number of rides
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(), rides.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int m = rides.size();
        vector<long long> dp(m + 1, 0);
        
        for (int i = 0; i < m; i++) {
            int start = rides[i][0];
            int end = rides[i][1];
            int tip = rides[i][2];
            long long earnings = end - start + tip;
            
            // Binary search for last ride that ends before current start
            int left = 0, right = i;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (rides[mid][1] <= start) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            
            // Take current ride or skip it
            if (rides[left][1] <= start) {
                dp[i + 1] = max(dp[i], dp[left + 1] + earnings);
            } else {
                dp[i + 1] = max(dp[i], earnings);
            }
        }
        
        return dp[m];
    }
};