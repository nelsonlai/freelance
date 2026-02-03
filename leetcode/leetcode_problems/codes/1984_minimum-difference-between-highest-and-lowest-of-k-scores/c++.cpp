/*
 * Problem: Minimum Difference Between Highest and Lowest of K Scores
 * Difficulty: Easy
 * Tags: array, sort, sliding window
 * 
 * Approach: Sort and use sliding window of size k
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int minDiff = INT_MAX;
        
        for (int i = 0; i <= (int)nums.size() - k; i++) {
            minDiff = min(minDiff, nums[i + k - 1] - nums[i]);
        }
        
        return minDiff;
    }
};