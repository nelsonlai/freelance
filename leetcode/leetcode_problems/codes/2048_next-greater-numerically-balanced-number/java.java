/**
 * Problem: Next Greater Numerically Balanced Number
 * Difficulty: Medium
 * Tags: math, hash
 * 
 * Approach: Check numbers starting from n+1, verify if balanced
 * Time Complexity: O(n * log n) in worst case
 * Space Complexity: O(1)
 */

class Solution {
    public int nextBeautifulNumber(int n) {
        int num = n + 1;
        
        while (true) {
            if (isBalanced(num)) {
                return num;
            }
            num++;
        }
    }
    
    private boolean isBalanced(int num) {
        int[] count = new int[10];
        String s = String.valueOf(num);
        
        for (char c : s.toCharArray()) {
            count[c - '0']++;
        }
        
        for (int i = 0; i < 10; i++) {
            if (count[i] > 0 && count[i] != i) {
                return false;
            }
        }
        
        return true;
    }
}