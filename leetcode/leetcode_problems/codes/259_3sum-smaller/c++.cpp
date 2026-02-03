/*
 * Problem: 3Sum Smaller
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int count = 0;
        
        for (int i = 0; i < (int)nums.size() - 2; i++) {
            int left = i + 1;
            int right = nums.size() - 1;
            
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] < target) {
                    count += right - left;
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return count;
    }
};