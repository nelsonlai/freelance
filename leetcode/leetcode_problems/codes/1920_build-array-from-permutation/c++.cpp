/*
 * Problem: Build Array from Permutation
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Build new array using nums as indices
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        vector<int> result(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            result[i] = nums[nums[i]];
        }
        return result;
    }
};