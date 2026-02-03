/**
 * Problem: Find Original Array From Doubled Array
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort
 * 
 * Approach: Sort and use greedy - match each number with its double
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[] findOriginalArray(int[] changed) {
        if (changed.length % 2 != 0) {
            return new int[0];
        }
        
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : changed) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        Arrays.sort(changed);
        List<Integer> result = new ArrayList<>();
        
        for (int num : changed) {
            if (count.get(num) == 0) {
                continue;
            }
            
            int doubleVal = num * 2;
            if (count.getOrDefault(doubleVal, 0) == 0) {
                return new int[0];
            }
            
            count.put(num, count.get(num) - 1);
            count.put(doubleVal, count.get(doubleVal) - 1);
            result.add(num);
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}