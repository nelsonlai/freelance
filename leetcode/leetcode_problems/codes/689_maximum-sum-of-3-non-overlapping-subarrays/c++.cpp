/*
 * Problem: Maximum Sum of 3 Non-Overlapping Subarrays
 * Difficulty: Hard
 * Tags: array, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        
        int total = prefixSum[k] - prefixSum[0];
        for (int i = k; i < n - 2 * k + 1; i++) {
            if (prefixSum[i] - prefixSum[i - k] > total) {
                total = prefixSum[i] - prefixSum[i - k];
                left[i] = i - k;
            } else {
                left[i] = left[i - 1];
            }
        }
        
        total = prefixSum[n] - prefixSum[n - k];
        right[n - k] = n - k;
        for (int i = n - k - 1; i >= 2 * k; i--) {
            if (prefixSum[i + k] - prefixSum[i] >= total) {
                total = prefixSum[i + k] - prefixSum[i];
                right[i] = i;
            } else {
                right[i] = right[i + 1];
            }
        }
        
        int maxSum = 0;
        vector<int> result(3);
        for (int i = k; i < n - 2 * k + 1; i++) {
            int l = left[i], r = right[i + k];
            int currentSum = (prefixSum[i + k] - prefixSum[i]) +
                           (prefixSum[l + k] - prefixSum[l]) +
                           (prefixSum[r + k] - prefixSum[r]);
            if (currentSum > maxSum) {
                maxSum = currentSum;
                result[0] = l;
                result[1] = i;
                result[2] = r;
            }
        }
        
        return result;
    }
};