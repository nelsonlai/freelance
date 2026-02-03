/*
 * Problem: Constrained Subsequence Sum
 * Difficulty: Hard
 * Tags: array, dp, queue, heap
 * 
 * Approach: DP with deque - dp[i] = max sum ending at i, use deque to track max in window
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(n) for DP and deque
 */

#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        deque<int> dq;
        
        for (int i = 0; i < n; i++) {
            while (!dq.empty() && dq.front() < i - k) {
                dq.pop_front();
            }
            
            dp[i] = nums[i];
            if (!dq.empty()) {
                dp[i] = max(dp[i], dp[dq.front()] + nums[i]);
            }
            
            while (!dq.empty() && dp[dq.back()] <= dp[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
        }
        
        int result = INT_MIN;
        for (int val : dp) {
            result = max(result, val);
        }
        return result;
    }
};