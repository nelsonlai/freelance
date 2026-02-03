/*
 * Problem: Reduction Operations to Make the Array Elements Equal
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Sort, count how many elements need to be reduced to each level
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result = 0;
        int distinct = 0;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i-1]) {
                distinct++;
            }
            result += distinct;
        }
        
        return result;
    }
};