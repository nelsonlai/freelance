/**
 * Problem: Patching Array
 * Difficulty: Hard
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int minPatches(int[] nums, int n) {
        int patches = 0;
        int i = 0;
        long miss = 1;
        
        while (miss <= n) {
            if (i < nums.length && nums[i] <= miss) {
                miss += nums[i];
                i++;
            } else {
                miss += miss;
                patches++;
            }
        }
        
        return patches;
    }
}