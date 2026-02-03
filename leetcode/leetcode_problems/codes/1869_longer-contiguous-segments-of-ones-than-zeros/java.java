/**
 * Problem: Longer Contiguous Segments of Ones than Zeros
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Find longest consecutive 1s and 0s, compare
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean checkZeroOnes(String s) {
        int maxOnes = 0, maxZeros = 0;
        int currentOnes = 0, currentZeros = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '1') {
                currentOnes++;
                currentZeros = 0;
                maxOnes = Math.max(maxOnes, currentOnes);
            } else {
                currentZeros++;
                currentOnes = 0;
                maxZeros = Math.max(maxZeros, currentZeros);
            }
        }
        
        return maxOnes > maxZeros;
    }
}