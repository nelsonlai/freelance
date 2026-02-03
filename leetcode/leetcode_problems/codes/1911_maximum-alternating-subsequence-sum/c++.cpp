/*
 * Problem: Maximum Alternating Subsequence Sum
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: DP - track max sum ending with even/odd index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long even = 0;  // max sum ending at even index (add)
        long long odd = 0;   // max sum ending at odd index (subtract)
        
        for (int num : nums) {
            long long newEven = max(even, odd + num);
            long long newOdd = max(odd, even - num);
            even = newEven;
            odd = newOdd;
        }
        
        return max(even, odd);
    }
};