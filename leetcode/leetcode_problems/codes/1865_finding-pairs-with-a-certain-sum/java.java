/**
 * Problem: Finding Pairs With a Certain Sum
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use hash map to count nums2, update on add
 * Time Complexity: O(1) for count, O(1) for add
 * Space Complexity: O(n)
 */

import java.util.*;

class FindSumPairs {
    private int[] nums1;
    private int[] nums2;
    private Map<Integer, Integer> count2;

    public FindSumPairs(int[] nums1, int[] nums2) {
        this.nums1 = nums1;
        this.nums2 = nums2;
        this.count2 = new HashMap<>();
        for (int num : nums2) {
            count2.put(num, count2.getOrDefault(num, 0) + 1);
        }
    }
    
    public void add(int index, int val) {
        int oldVal = nums2[index];
        count2.put(oldVal, count2.get(oldVal) - 1);
        if (count2.get(oldVal) == 0) {
            count2.remove(oldVal);
        }
        
        int newVal = oldVal + val;
        nums2[index] = newVal;
        count2.put(newVal, count2.getOrDefault(newVal, 0) + 1);
    }
    
    public int count(int tot) {
        int result = 0;
        for (int num : nums1) {
            int target = tot - num;
            result += count2.getOrDefault(target, 0);
        }
        return result;
    }
}