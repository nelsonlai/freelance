/**
 * Problem: Unique Number of Occurrences
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Count frequencies, check if all frequencies are unique
 * Time Complexity: O(n) where n is the length of arr
 * Space Complexity: O(n) for frequency map
 */
import java.util.*;

class Solution {
    public boolean uniqueOccurrences(int[] arr) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int num : arr) {
            freq.put(num, freq.getOrDefault(num, 0) + 1);
        }
        
        Set<Integer> occurrences = new HashSet<>(freq.values());
        return occurrences.size() == freq.size();
    }
}