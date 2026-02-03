/**
 * Problem: Minimum Time to Type Word Using Special Typewriter
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Calculate min distance between consecutive characters (clockwise or counterclockwise)
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int minTimeToType(String word) {
        int time = 0;
        char current = 'a';
        
        for (char c : word.toCharArray()) {
            int diff = Math.abs(c - current);
            time += Math.min(diff, 26 - diff) + 1;  // +1 for typing
            current = c;
        }
        
        return time;
    }
}