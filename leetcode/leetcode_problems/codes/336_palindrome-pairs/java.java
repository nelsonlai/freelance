/**
 * Problem: Palindrome Pairs
 * Difficulty: Hard
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<List<Integer>> palindromePairs(String[] words) {
        Map<String, Integer> wordMap = new HashMap<>();
        for (int i = 0; i < words.length; i++) {
            wordMap.put(words[i], i);
        }
        
        List<List<Integer>> result = new ArrayList<>();
        
        for (int i = 0; i < words.length; i++) {
            String word = words[i];
            for (int j = 0; j <= word.length(); j++) {
                String prefix = word.substring(0, j);
                String suffix = word.substring(j);
                
                if (isPalindrome(prefix)) {
                    String revSuffix = new StringBuilder(suffix).reverse().toString();
                    if (wordMap.containsKey(revSuffix) && wordMap.get(revSuffix) != i) {
                        result.add(Arrays.asList(wordMap.get(revSuffix), i));
                    }
                }
                
                if (j != word.length() && isPalindrome(suffix)) {
                    String revPrefix = new StringBuilder(prefix).reverse().toString();
                    if (wordMap.containsKey(revPrefix) && wordMap.get(revPrefix) != i) {
                        result.add(Arrays.asList(i, wordMap.get(revPrefix)));
                    }
                }
            }
        }
        
        return result;
    }
    
    private boolean isPalindrome(String s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s.charAt(left++) != s.charAt(right--)) {
                return false;
            }
        }
        return true;
    }
}