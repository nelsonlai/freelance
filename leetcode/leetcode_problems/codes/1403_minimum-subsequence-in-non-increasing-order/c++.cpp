/*
 * Problem: Minimum Subsequence in Non-Increasing Order
 * Difficulty: Easy
 * Tags: array, greedy, sort
 * 
 * Approach: Sort descending, greedily take largest numbers until sum > remaining
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for result
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        vector<int> result;
        int currentSum = 0;
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            result.push_back(nums[i]);
            currentSum += nums[i];
            if (currentSum > total - currentSum) {
                break;
            }
        }
        
        return result;
    }
};