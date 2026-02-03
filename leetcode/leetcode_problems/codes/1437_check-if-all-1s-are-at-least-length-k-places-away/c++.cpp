/*
 * Problem: Check If All 1's Are at Least Length K Places Away
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Track last position of 1, check distance to current 1
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(1)
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int lastOne = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                if (i - lastOne <= k) {
                    return false;
                }
                lastOne = i;
            }
        }
        return true;
    }
};