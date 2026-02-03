/*
 * Problem: String to Integer (atoi)
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class Solution {
    public int MyAtoi(string s) {
        s = s.Trim();
        if (string.IsNullOrEmpty(s)) {
            return 0;
        }
        
        int sign = 1;
        int i = 0;
        
        if (s[0] == '-') {
            sign = -1;
            i = 1;
        } else if (s[0] == '+') {
            i = 1;
        }
        
        int result = 0;
        while (i < s.Length && char.IsDigit(s[i])) {
            int digit = s[i] - '0';
            if (result > int.MaxValue / 10 || 
                (result == int.MaxValue / 10 && digit > 7)) {
                return sign == 1 ? int.MaxValue : int.MinValue;
            }
            result = result * 10 + digit;
            i++;
        }
        
        return sign * result;
    }
}