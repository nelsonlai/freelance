/**
 * Problem: Maximum Product of the Length of Two Palindromic Substrings
 * Difficulty: Hard
 * Tags: string, Manacher's algorithm, palindrome
 * 
 * Approach: Use Manacher's algorithm to find all palindromes, maximize product
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public long maxProduct(String s) {
        int n = s.length();
        int[] palLengths = manacher(s);
        
        // Find max product of two non-overlapping palindromes
        long maxProduct = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len1 = (i < palLengths.length) ? palLengths[i] : 1;
                int len2 = (j < palLengths.length) ? palLengths[j] : 1;
                
                // Check if they don't overlap
                int start1 = i - (len1 - 1) / 2;
                int end1 = i + len1 / 2;
                int start2 = j - (len2 - 1) / 2;
                int end2 = j + len2 / 2;
                
                if (end1 < start2) {
                    maxProduct = Math.max(maxProduct, (long) len1 * len2);
                }
            }
        }
        
        return maxProduct;
    }
    
    private int[] manacher(String s) {
        StringBuilder sb = new StringBuilder();
        sb.append('#');
        for (char c : s.toCharArray()) {
            sb.append(c).append('#');
        }
        String sNew = sb.toString();
        int nNew = sNew.length();
        int[] p = new int[nNew];
        int center = 0, right = 0;
        
        for (int i = 0; i < nNew; i++) {
            if (i < right) {
                p[i] = Math.min(right - i, p[2 * center - i]);
            }
            
            while (i + p[i] + 1 < nNew && i - p[i] - 1 >= 0 &&
                   sNew.charAt(i + p[i] + 1) == sNew.charAt(i - p[i] - 1)) {
                p[i]++;
            }
            
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        
        // Extract palindrome lengths for original string positions
        int[] result = new int[s.length()];
        for (int i = 1; i < nNew - 1; i += 2) {
            int origPos = (i - 1) / 2;
            result[origPos] = p[i];
        }
        
        return result;
    }
}
