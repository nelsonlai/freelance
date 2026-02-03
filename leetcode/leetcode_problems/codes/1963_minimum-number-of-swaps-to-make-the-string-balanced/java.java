/**
 * Problem: Minimum Number of Swaps to Make the String Balanced
 * Difficulty: Medium
 * Tags: array, string, greedy, stack
 * 
 * Approach: Count unmatched closing brackets, need (count+1)//2 swaps
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int minSwaps(String s) {
        int balance = 0;
        int maxUnmatched = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '[') {
                balance++;
            } else {
                balance--;
            }
            maxUnmatched = Math.max(maxUnmatched, -balance);
        }
        
        return (maxUnmatched + 1) / 2;
    }
}