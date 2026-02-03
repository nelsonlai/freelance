/**
 * Problem: Count and Say
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String countAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        
        String result = "1";
        for (int i = 1; i < n; i++) {
            StringBuilder newResult = new StringBuilder();
            int j = 0;
            while (j < result.length()) {
                int count = 1;
                while (j + 1 < result.length() && result.charAt(j) == result.charAt(j + 1)) {
                    count++;
                    j++;
                }
                newResult.append(count);
                newResult.append(result.charAt(j));
                j++;
            }
            result = newResult.toString();
        }
        
        return result;
    }
}