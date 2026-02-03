/*
 * Problem: Count and Say
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Text;

public class Solution {
    public string CountAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        
        string result = "1";
        for (int i = 1; i < n; i++) {
            StringBuilder newResult = new StringBuilder();
            int j = 0;
            while (j < result.Length) {
                int count = 1;
                while (j + 1 < result.Length && result[j] == result[j + 1]) {
                    count++;
                    j++;
                }
                newResult.Append(count);
                newResult.Append(result[j]);
                j++;
            }
            result = newResult.ToString();
        }
        
        return result;
    }
}