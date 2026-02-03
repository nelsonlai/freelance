/**
 * Problem: Max Difference You Can Get From Changing an Integer
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: For max, replace first non-9 digit with 9. For min, replace first non-0/1 digit with 0/1
 * Time Complexity: O(log num)
 * Space Complexity: O(log num)
 */

class Solution {
    public int maxDiff(int num) {
        String s = String.valueOf(num);
        
        String maxStr = s;
        for (char c : s.toCharArray()) {
            if (c != '9') {
                maxStr = s.replace(c, '9');
                break;
            }
        }
        
        String minStr = s;
        if (s.charAt(0) != '1') {
            minStr = s.replace(s.charAt(0), '1');
        } else {
            for (int i = 1; i < s.length(); i++) {
                char c = s.charAt(i);
                if (c != '0' && c != '1') {
                    minStr = s.replace(c, '0');
                    break;
                }
            }
        }
        
        return Integer.parseInt(maxStr) - Integer.parseInt(minStr);
    }
}