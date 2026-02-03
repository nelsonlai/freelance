/*
 * Problem: Range Sum of Sorted Subarray Sums
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int MOD = 1000000007;
        vector<long long> subarray_sums;
        
        for (int i = 0; i < n; i++) {
            long long current_sum = 0;
            for (int j = i; j < n; j++) {
                current_sum += nums[j];
                subarray_sums.push_back(current_sum);
            }
        }
        
        sort(subarray_sums.begin(), subarray_sums.end());
        long long result = 0;
        for (int i = left - 1; i < right; i++) {
            result = (result + subarray_sums[i]) % MOD;
        }
        
        return (int) result;
    }
};