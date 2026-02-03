/**
 * Problem: Find Longest Awesome Substring
 * Difficulty: Hard
 * Tags: string, tree, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int longestAwesome(String s) {
        Map<Integer, Integer> maskMap = new HashMap<>();
        maskMap.put(0, -1);
        int mask = 0;
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            int digit = s.charAt(i) - '0';
            mask ^= 1 << digit;
            
            if (maskMap.containsKey(mask)) {
                maxLen = Math.max(maxLen, i - maskMap.get(mask));
            } else {
                maskMap.put(mask, i);
            }
            
            for (int j = 0; j < 10; j++) {
                int tempMask = mask ^ (1 << j);
                if (maskMap.containsKey(tempMask)) {
                    maxLen = Math.max(maxLen, i - maskMap.get(tempMask));
                }
            }
        }
        
        return maxLen;
    }
}