/**
 * Problem: Smallest Range Covering Elements from K Lists
 * Difficulty: Hard
 * Tags: array, greedy, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[] smallestRange(List<List<Integer>> nums) {
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        int maxVal = Integer.MIN_VALUE;
        
        for (int i = 0; i < nums.size(); i++) {
            heap.offer(new int[]{nums.get(i).get(0), i, 0});
            maxVal = Math.max(maxVal, nums.get(i).get(0));
        }
        
        int[] result = {heap.peek()[0], maxVal};
        int[] pointers = new int[nums.size()];
        
        while (true) {
            int[] curr = heap.poll();
            int val = curr[0], listIdx = curr[1], idx = curr[2];
            
            if (maxVal - val < result[1] - result[0]) {
                result[0] = val;
                result[1] = maxVal;
            }
            
            if (idx + 1 >= nums.get(listIdx).size()) {
                break;
            }
            
            int nextVal = nums.get(listIdx).get(idx + 1);
            maxVal = Math.max(maxVal, nextVal);
            heap.offer(new int[]{nextVal, listIdx, idx + 1});
        }
        
        return result;
    }
}