/**
 * Problem: Shuffle an Array
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    private int[] original;
    private int[] nums;

    public Solution(int[] nums) {
        this.original = nums.clone();
        this.nums = nums.clone();
    }
    
    public int[] reset() {
        nums = original.clone();
        return nums;
    }
    
    public int[] shuffle() {
        Random rand = new Random();
        for (int i = nums.length - 1; i > 0; i--) {
            int j = rand.nextInt(i + 1);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        return nums;
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int[] param_1 = obj.reset();
 * int[] param_2 = obj.shuffle();
 */