/**
 * Problem: Ransom Note
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean canConstruct(String ransomNote, String magazine) {
        Map<Character, Integer> magazineCount = new HashMap<>();
        for (char c : magazine.toCharArray()) {
            magazineCount.put(c, magazineCount.getOrDefault(c, 0) + 1);
        }
        
        for (char c : ransomNote.toCharArray()) {
            int count = magazineCount.getOrDefault(c, 0);
            if (count == 0) {
                return false;
            }
            magazineCount.put(c, count - 1);
        }
        
        return true;
    }
}