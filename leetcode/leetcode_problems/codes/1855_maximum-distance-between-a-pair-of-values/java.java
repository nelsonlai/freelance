/**
 * Problem: Maximum Distance Between a Pair of Values
 * Difficulty: Medium
 * Tags: array, search, two pointers
 * 
 * Approach: Two pointers - for each i, find rightmost j where nums1[i] <= nums2[j]
 * Time Complexity: O(n + m) where n, m are array lengths
 * Space Complexity: O(1)
 */

class Solution {
    public int maxDistance(int[] nums1, int[] nums2) {
        int result = 0;
        int j = 0;
        
        for (int i = 0; i < nums1.length; i++) {
            while (j < nums2.length && nums1[i] <= nums2[j]) {
                j++;
            }
            
            if (j > i + 1) {
                result = Math.max(result, j - 1 - i);
            }
        }
        
        return result;
    }
}