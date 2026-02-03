/*
 * Problem: Optimal Division
 * Difficulty: Medium
 * Tags: array, string, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        if (nums.size() == 1) {
            return to_string(nums[0]);
        }
        if (nums.size() == 2) {
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        }
        
        string result = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            result += "/" + to_string(nums[i]);
        }
        result += ")";
        
        return result;
    }
};