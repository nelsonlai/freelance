/**
 * Problem: Find the Kth Largest Integer in the Array
 * Difficulty: Medium
 * Tags: array, string, sort, queue, heap
 * 
 * Approach: Sort by integer value, return k-th largest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public String kthLargestNumber(String[] nums, int k) {
        Arrays.sort(nums, (a, b) -> {
            if (a.length() != b.length()) {
                return Integer.compare(b.length(), a.length());
            }
            return b.compareTo(a);
        });
        return nums[k - 1];
    }
}