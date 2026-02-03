/**
 * Problem: Integer to English Words
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    private final String[] ones = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    private final String[] teens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    private final String[] tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    private final String[] thousands = {"", "Thousand", "Million", "Billion"};
    
    public String numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        
        StringBuilder result = new StringBuilder();
        int i = 0;
        
        while (num > 0) {
            if (num % 1000 != 0) {
                result.insert(0, helper(num % 1000) + thousands[i] + " ");
            }
            num /= 1000;
            i++;
        }
        
        return result.toString().trim();
    }
    
    private String helper(int n) {
        if (n == 0) {
            return "";
        } else if (n < 10) {
            return ones[n] + " ";
        } else if (n < 20) {
            return teens[n - 10] + " ";
        } else if (n < 100) {
            return tens[n / 10] + " " + helper(n % 10);
        } else {
            return ones[n / 100] + " Hundred " + helper(n % 100);
        }
    }
}