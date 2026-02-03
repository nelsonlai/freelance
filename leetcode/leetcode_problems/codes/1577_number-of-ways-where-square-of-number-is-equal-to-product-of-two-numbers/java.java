/**
 * Problem: Number of Ways Where Square of Number Is Equal to Product of Two Numbers
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int numTriplets(int[] nums1, int[] nums2) {
        return countTriplets(nums1, nums2) + countTriplets(nums2, nums1);
    }
    
    private int countTriplets(int[] arr1, int[] arr2) {
        Map<Long, Integer> freq = new HashMap<>();
        for (long num : arr2) {
            freq.put(num, freq.getOrDefault(num, 0) + 1);
        }
        
        int result = 0;
        for (long num : arr1) {
            long target = num * num;
            for (Map.Entry<Long, Integer> entry : freq.entrySet()) {
                long a = entry.getKey();
                if (target % a == 0) {
                    long b = target / a;
                    if (freq.containsKey(b)) {
                        if (a == b) {
                            result += entry.getValue() * (entry.getValue() - 1);
                        } else {
                            result += entry.getValue() * freq.get(b);
                        }
                    }
                }
            }
        }
        
        return result / 2;
    }
}