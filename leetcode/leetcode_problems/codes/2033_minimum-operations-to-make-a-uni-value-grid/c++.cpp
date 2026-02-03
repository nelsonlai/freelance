/*
 * Problem: Minimum Operations to Make a Uni-Value Grid
 * Difficulty: Medium
 * Tags: array, math, sort
 * 
 * Approach: Find median value, calculate operations needed to make all cells equal
 * Time Complexity: O(mn log(mn)) for sorting
 * Space Complexity: O(mn)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;
        for (auto& row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }
        
        // Check if all can be made equal modulo x
        int remainder = nums[0] % x;
        for (int num : nums) {
            if (num % x != remainder) {
                return -1;
            }
        }
        
        // Normalize all numbers
        vector<int> normalized;
        for (int num : nums) {
            normalized.push_back((num - remainder) / x);
        }
        
        sort(normalized.begin(), normalized.end());
        int median = normalized[normalized.size() / 2];
        
        int result = 0;
        for (int num : normalized) {
            result += abs(num - median);
        }
        
        return result;
    }
};