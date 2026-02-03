/*
 * Problem: Number of Subsequences That Satisfy the Given Sum Condition
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int MOD = 1000000007;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // Precompute powers of 2
        vector<long long> power(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            power[i] = (power[i - 1] * 2) % MOD;
        }
        
        long long result = 0;
        int left = 0, right = n - 1;
        
        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                result = (result + power[right - left]) % MOD;
                left++;
            } else {
                right--;
            }
        }
        
        return (int) result;
    }
};