/*
 * Problem: Maximum Average Subarray I
 * Difficulty: Easy
 * Tags: array
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
    double findMaxAverage(vector<int>& nums, int k) {
        long long windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
        }
        long long maxSum = windowSum;
        
        for (int i = k; i < nums.size(); i++) {
            windowSum = windowSum - nums[i-k] + nums[i];
            maxSum = max(maxSum, windowSum);
        }
        
        return (double)maxSum / k;
    }
};