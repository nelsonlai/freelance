/**
 * Problem: Array With Elements Not Equal to Average of Neighbors
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort and interleave small and large elements
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] rearrangeArray(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        int[] result = new int[n];
        
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
}