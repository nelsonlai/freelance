/*
 * Problem: Add Binary
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Text;

public class Solution {
    public string AddBinary(string a, string b) {
        StringBuilder result = new StringBuilder();
        int carry = 0;
        int i = a.Length - 1;
        int j = b.Length - 1;
        
        while (i >= 0 || j >= 0 || carry > 0) {
            int total = carry;
            if (i >= 0) {
                total += a[i--] - '0';
            }
            if (j >= 0) {
                total += b[j--] - '0';
            }
            result.Append(total % 2);
            carry = total / 2;
        }
        
        char[] chars = result.ToString().ToCharArray();
        System.Array.Reverse(chars);
        return new string(chars);
    }
}