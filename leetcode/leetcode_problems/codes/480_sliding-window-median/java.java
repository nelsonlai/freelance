/**
 * Problem: Sliding Window Median
 * Difficulty: Hard
 * Tags: array, hash, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public double[] medianSlidingWindow(int[] nums, int k) {
        List<Integer> window = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            window.add(nums[i]);
        }
        Collections.sort(window);
        
        double[] result = new double[nums.length - k + 1];
        result[0] = getMedian(window, k);
        
        for (int i = k; i < nums.length; i++) {
            window.remove(Integer.valueOf(nums[i - k]));
            int insertPos = Collections.binarySearch(window, nums[i]);
            if (insertPos < 0) {
                insertPos = -(insertPos + 1);
            }
            window.add(insertPos, nums[i]);
            result[i - k + 1] = getMedian(window, k);
        }
        
        return result;
    }
    
    private double getMedian(List<Integer> window, int k) {
        if (k % 2 == 0) {
            return ((double)window.get(k/2-1) + window.get(k/2)) / 2.0;
        } else {
            return (double)window.get(k/2);
        }
    }
}