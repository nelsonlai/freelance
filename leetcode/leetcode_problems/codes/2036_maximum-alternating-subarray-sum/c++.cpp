/*
 * Problem: Maximum Alternating Subarray Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - track max sum ending at each position with even/odd index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    long long maximumAlternatingSubarraySum(vector<int>& nums) {
        // dp[0] = max sum ending here with even index (add)
        // dp[1] = max sum ending here with odd index (subtract)
        long long dpEven = nums[0];
        long long dpOdd = LLONG_MIN;
        long long result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            long long newDpEven, newDpOdd;
            
            // Current position is even index (i % 2 == 0 means even position)
            if (i % 2 == 0) {
                // Can continue from previous even or start new
                newDpEven = max((long long)nums[i], dpOdd != LLONG_MIN ? dpOdd + nums[i] : (long long)nums[i]);
                // Can continue from previous odd
                newDpOdd = dpOdd != LLONG_MIN ? dpOdd + nums[i] : LLONG_MIN;
            } else {
                // Current position is odd index
                // Can continue from previous even
                newDpOdd = dpEven - nums[i];
                // Can continue from previous odd or start new
                newDpEven = dpEven;
            }
            
            dpEven = newDpEven;
            dpOdd = newDpOdd;
            
            result = max(result, max(dpEven, dpOdd != LLONG_MIN ? dpOdd : LLONG_MIN));
        }
        
        return result;
    }
};