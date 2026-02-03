/**
 * Problem: Find the Closest Palindrome
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String nearestPalindromic(String n) {
        int length = n.length();
        long num = Long.parseLong(n);
        
        Set<Long> candidates = new HashSet<>();
        candidates.add((long)Math.pow(10, length - 1) - 1);
        candidates.add((long)Math.pow(10, length) + 1);
        
        long prefix = Long.parseLong(n.substring(0, (length + 1) / 2));
        for (long i = -1; i <= 1; i++) {
            String candidate = String.valueOf(prefix + i);
            if (length % 2 == 0) {
                candidate += new StringBuilder(candidate).reverse().toString();
            } else {
                candidate += new StringBuilder(candidate.substring(0, candidate.length() - 1)).reverse().toString();
            }
            candidates.add(Long.parseLong(candidate));
        }
        
        candidates.remove(num);
        
        long result = 0;
        long minDiff = Long.MAX_VALUE;
        for (long candidate : candidates) {
            long diff = Math.abs(candidate - num);
            if (diff < minDiff || (diff == minDiff && candidate < result)) {
                minDiff = diff;
                result = candidate;
            }
        }
        
        return String.valueOf(result);
    }
}