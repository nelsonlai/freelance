/**
 * Problem: Multiply Strings
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String multiply(String num1, String num2) {
        if (num1.equals("0") || num2.equals("0")) {
            return "0";
        }
        
        int m = num1.length(), n = num2.length();
        int[] result = new int[m + n];
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1.charAt(i) - '0') * (num2.charAt(j) - '0');
                int p1 = i + j, p2 = i + j + 1;
                int total = mul + result[p2];
                
                result[p2] = total % 10;
                result[p1] += total / 10;
            }
        }
        
        // Remove leading zeros
        StringBuilder sb = new StringBuilder();
        int start = 0;
        while (start < result.length && result[start] == 0) {
            start++;
        }
        for (int i = start; i < result.length; i++) {
            sb.append(result[i]);
        }
        
        return sb.toString();
    }
}