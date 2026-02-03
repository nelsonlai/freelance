/**
 * Problem: Create Maximum Number
 * Difficulty: Hard
 * Tags: array, greedy, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int[] maxNumber(int[] nums1, int[] nums2, int k) {
        int m = nums1.length;
        int n = nums2.length;
        int[] result = new int[k];
        
        for (int i = Math.max(0, k - n); i <= Math.min(k, m); i++) {
            int[] candidate = merge(getMax(nums1, i), getMax(nums2, k - i));
            if (greater(candidate, 0, result, 0)) {
                result = candidate;
            }
        }
        
        return result;
    }
    
    private int[] getMax(int[] nums, int k) {
        int[] result = new int[k];
        int drop = nums.length - k;
        Stack<Integer> stack = new Stack<>();
        
        for (int num : nums) {
            while (drop > 0 && !stack.isEmpty() && stack.peek() < num) {
                stack.pop();
                drop--;
            }
            stack.push(num);
        }
        
        while (stack.size() > k) {
            stack.pop();
        }
        
        for (int i = k - 1; i >= 0; i--) {
            result[i] = stack.pop();
        }
        
        return result;
    }
    
    private int[] merge(int[] nums1, int[] nums2) {
        int[] result = new int[nums1.length + nums2.length];
        int i = 0, j = 0, k = 0;
        
        while (i < nums1.length || j < nums2.length) {
            if (i >= nums1.length) {
                result[k++] = nums2[j++];
            } else if (j >= nums2.length) {
                result[k++] = nums1[i++];
            } else if (greater(nums1, i, nums2, j)) {
                result[k++] = nums1[i++];
            } else {
                result[k++] = nums2[j++];
            }
        }
        
        return result;
    }
    
    private boolean greater(int[] nums1, int i, int[] nums2, int j) {
        while (i < nums1.length && j < nums2.length && nums1[i] == nums2[j]) {
            i++;
            j++;
        }
        return j == nums2.length || (i < nums1.length && nums1[i] > nums2[j]);
    }
}