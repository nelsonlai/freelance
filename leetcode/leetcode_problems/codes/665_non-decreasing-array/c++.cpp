/*
 * Problem: Non-decreasing Array
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int count = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i-1]) {
                count++;
                if (count > 1) {
                    return false;
                }
                if (i > 1 && nums[i] < nums[i-2]) {
                    nums[i] = nums[i-1];
                }
            }
        }
        return true;
    }
};