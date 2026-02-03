/*
 * Problem: Split Array Largest Sum
 * Difficulty: Hard
 * Tags: array, dp, greedy, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    bool canSplit(vector<int>& nums, int maxSum, int k) {
        int splits = 1;
        int currentSum = 0;
        for (int num : nums) {
            if (currentSum + num > maxSum) {
                splits++;
                currentSum = num;
            } else {
                currentSum += num;
            }
        }
        return splits <= k;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (canSplit(nums, mid, k)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};