/**
 * Problem: Palindrome Permutation II
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<String> generatePalindromes(String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        List<Character> oddChars = new ArrayList<>();
        for (Map.Entry<Character, Integer> entry : count.entrySet()) {
            if (entry.getValue() % 2 == 1) {
                oddChars.add(entry.getKey());
            }
        }
        
        if (oddChars.size() > 1) {
            return new ArrayList<>();
        }
        
        String mid = oddChars.isEmpty() ? "" : String.valueOf(oddChars.get(0));
        List<Character> half = new ArrayList<>();
        for (Map.Entry<Character, Integer> entry : count.entrySet()) {
            for (int i = 0; i < entry.getValue() / 2; i++) {
                half.add(entry.getKey());
            }
        }
        
        List<String> result = new ArrayList<>();
        permute(half, 0, mid, result);
        return result;
    }
    
    private void permute(List<Character> chars, int start, String mid, List<String> result) {
        if (start == chars.size()) {
            StringBuilder sb = new StringBuilder();
            for (char c : chars) {
                sb.append(c);
            }
            String first = sb.toString();
            sb.reverse();
            result.add(first + mid + sb.toString());
            return;
        }
        
        Set<Character> seen = new HashSet<>();
        for (int i = start; i < chars.size(); i++) {
            if (!seen.contains(chars.get(i))) {
                seen.add(chars.get(i));
                Collections.swap(chars, start, i);
                permute(chars, start + 1, mid, result);
                Collections.swap(chars, start, i);
            }
        }
    }
}