/*
 * Problem: Minimize Maximum Pair Sum in Array
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort, pair smallest with largest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result = 0;
        int n = nums.size();
        for (int i = 0; i < n / 2; i++) {
            result = max(result, nums[i] + nums[n - 1 - i]);
        }
        return result;
    }
};