/*
 * Problem: Multiply Strings
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class Solution {
    public string Multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        
        int m = num1.Length, n = num2.Length;
        int[] result = new int[m + n];
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int total = mul + result[p2];
                
                result[p2] = total % 10;
                result[p1] += total / 10;
            }
        }
        
        // Remove leading zeros
        System.Text.StringBuilder sb = new System.Text.StringBuilder();
        int start = 0;
        while (start < result.Length && result[start] == 0) {
            start++;
        }
        for (int i = start; i < result.Length; i++) {
            sb.Append(result[i]);
        }
        
        return sb.ToString();
    }
}