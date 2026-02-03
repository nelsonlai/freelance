/**
 * Problem: Least Number of Unique Integers after K Removals
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findLeastNumOfUniqueInts(int[] arr, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int num : arr) {
            freq.put(num, freq.getOrDefault(num, 0) + 1);
        }
        
        List<Integer> sortedFreq = new ArrayList<>(freq.values());
        Collections.sort(sortedFreq);
        
        int removed = 0;
        for (int count : sortedFreq) {
            if (k >= count) {
                k -= count;
                removed++;
            } else {
                break;
            }
        }
        
        return sortedFreq.size() - removed;
    }
}