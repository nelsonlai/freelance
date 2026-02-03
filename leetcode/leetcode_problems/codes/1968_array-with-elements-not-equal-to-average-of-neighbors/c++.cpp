/*
 * Problem: Array With Elements Not Equal to Average of Neighbors
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort and interleave small and large elements
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> result(n);
        
        int left = 0, right = n - 1;
        int idx = 0;
        
        while (left <= right) {
            if (left == right) {
                result[idx++] = nums[left];
                break;
            }
            result[idx++] = nums[left++];
            result[idx++] = nums[right--];
        }
        
        return result;
    }
};