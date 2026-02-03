/**
 * Problem: Kth Distinct String in an Array
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Count occurrences, find kth distinct string
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String kthDistinct(String[] arr, int k) {
        Map<String, Integer> count = new HashMap<>();
        for (String s : arr) {
            count.put(s, count.getOrDefault(s, 0) + 1);
        }
        
        int distinctCount = 0;
        for (String s : arr) {
            if (count.get(s) == 1) {
                distinctCount++;
                if (distinctCount == k) {
                    return s;
                }
            }
        }
        
        return "";
    }
}