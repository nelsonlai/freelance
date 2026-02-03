/**
 * Problem: Maximum Product of the Length of Two Palindromic Subsequences
 * Difficulty: Medium
 * Tags: string, dp, bitmask
 * 
 * Approach: Use bitmask to enumerate all subsequences, find palindromic ones, maximize product
 * Time Complexity: O(3^n) where n is length
 * Space Complexity: O(2^n)
 */

import java.util.*;

class Solution {
    public int maxProduct(String s) {
        int n = s.length();
        List<Integer> palindromes = new ArrayList<>();
        
        // Find all palindromic subsequences
        for (int mask = 1; mask < (1 << n); mask++) {
            StringBuilder subseq = new StringBuilder();
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    subseq.append(s.charAt(i));
                }
            }
            
            String str = subseq.toString();
            if (isPalindrome(str)) {
                palindromes.add(mask);
            }
        }
        
        int maxProduct = 0;
        
        // Find two non-overlapping palindromic subsequences
        for (int i = 0; i < palindromes.size(); i++) {
            for (int j = i + 1; j < palindromes.size(); j++) {
                if ((palindromes.get(i) & palindromes.get(j)) == 0) {  // No overlap
                    int len1 = Integer.bitCount(palindromes.get(i));
                    int len2 = Integer.bitCount(palindromes.get(j));
                    maxProduct = Math.max(maxProduct, len1 * len2);
                }
            }
        }
        
        return maxProduct;
    }
    
    private boolean isPalindrome(String s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s.charAt(left) != s.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
}