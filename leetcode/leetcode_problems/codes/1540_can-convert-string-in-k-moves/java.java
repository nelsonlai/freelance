/**
 * Problem: Can Convert String in K Moves
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean canConvertString(String s, String t, int k) {
        if (s.length() != t.length()) {
            return false;
        }
        
        Map<Integer, Integer> shifts = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            int shift = ((t.charAt(i) - s.charAt(i)) % 26 + 26) % 26;
            if (shift > 0) {
                shifts.put(shift, shifts.getOrDefault(shift, 0) + 1);
            }
        }
        
        for (Map.Entry<Integer, Integer> entry : shifts.entrySet()) {
            int shift = entry.getKey();
            int count = entry.getValue();
            int maxShift = shift + 26 * (count - 1);
            if (maxShift > k) {
                return false;
            }
        }
        
        return true;
    }
}