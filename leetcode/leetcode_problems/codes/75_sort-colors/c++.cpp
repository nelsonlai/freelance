/*
 * Problem: Sort Colors
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int i = 0;
        
        while (i <= right) {
            if (nums[i] == 0) {
                swap(nums[left], nums[i]);
                left++;
                i++;
            } else if (nums[i] == 2) {
                swap(nums[right], nums[i]);
                right--;
            } else {
                i++;
            }
        }
    }
};