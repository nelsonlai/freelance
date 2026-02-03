/**
 * Problem: Minimum Index Sum of Two Lists
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String[] findRestaurant(String[] list1, String[] list2) {
        Map<String, Integer> indexMap = new HashMap<>();
        for (int i = 0; i < list1.length; i++) {
            indexMap.put(list1[i], i);
        }
        
        int minSum = Integer.MAX_VALUE;
        List<String> result = new ArrayList<>();
        
        for (int j = 0; j < list2.length; j++) {
            if (indexMap.containsKey(list2[j])) {
                int indexSum = indexMap.get(list2[j]) + j;
                if (indexSum < minSum) {
                    minSum = indexSum;
                    result.clear();
                    result.add(list2[j]);
                } else if (indexSum == minSum) {
                    result.add(list2[j]);
                }
            }
        }
        
        return result.toArray(new String[0]);
    }
}