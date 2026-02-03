/**
 * Problem: Add Binary
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String addBinary(String a, String b) {
        StringBuilder result = new StringBuilder();
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        
        while (i >= 0 || j >= 0 || carry > 0) {
            int total = carry;
            if (i >= 0) {
                total += a.charAt(i--) - '0';
            }
            if (j >= 0) {
                total += b.charAt(j--) - '0';
            }
            result.append(total % 2);
            carry = total / 2;
        }
        
        return result.reverse().toString();
    }
}