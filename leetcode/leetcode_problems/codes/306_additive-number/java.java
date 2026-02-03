/**
 * Problem: Additive Number
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean isAdditiveNumber(String num) {
        int n = num.length();
        for (int i = 1; i <= n / 2; i++) {
            if (num.charAt(0) == '0' && i > 1) break;
            long num1 = Long.parseLong(num.substring(0, i));
            
            for (int j = i + 1; j < n; j++) {
                if (num.charAt(i) == '0' && j > i + 1) break;
                long num2 = Long.parseLong(num.substring(i, j));
                
                if (isValid(num1, num2, num, j)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    private boolean isValid(long num1, long num2, String num, int start) {
        if (start == num.length()) return true;
        
        long sum = num1 + num2;
        String sumStr = String.valueOf(sum);
        
        if (!num.startsWith(sumStr, start)) return false;
        
        return isValid(num2, sum, num, start + sumStr.length());
    }
}