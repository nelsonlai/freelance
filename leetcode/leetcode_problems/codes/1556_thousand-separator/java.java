/**
 * Problem: Thousand Separator
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String thousandSeparator(int n) {
        String s = String.valueOf(n);
        StringBuilder result = new StringBuilder();
        for (int i = s.length() - 1; i >= 0; i--) {
            if (result.length() > 0 && (s.length() - 1 - i) % 3 == 0) {
                result.append('.');
            }
            result.append(s.charAt(i));
        }
        return result.reverse().toString();
    }
}