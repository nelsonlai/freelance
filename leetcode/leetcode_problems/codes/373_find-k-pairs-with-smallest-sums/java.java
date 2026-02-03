/**
 * Problem: Find K Pairs with Smallest Sums
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<List<Integer>> kSmallestPairs(int[] nums1, int[] nums2, int k) {
        if (nums1.length == 0 || nums2.length == 0) {
            return new ArrayList<>();
        }
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> 
            (nums1[a[0]] + nums2[a[1]]) - (nums1[b[0]] + nums2[b[1]]));
        
        for (int i = 0; i < Math.min(k, nums1.length); i++) {
            heap.offer(new int[]{i, 0});
        }
        
        List<List<Integer>> result = new ArrayList<>();
        while (!heap.isEmpty() && result.size() < k) {
            int[] pair = heap.poll();
            result.add(Arrays.asList(nums1[pair[0]], nums2[pair[1]]));
            
            if (pair[1] + 1 < nums2.length) {
                heap.offer(new int[]{pair[0], pair[1] + 1});
            }
        }
        
        return result;
    }
}