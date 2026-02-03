/**
 * Problem: Find the Winner of an Array Game
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int getWinner(int[] arr, int k) {
        if (k >= arr.length) {
            int max = arr[0];
            for (int num : arr) {
                max = Math.max(max, num);
            }
            return max;
        }
        
        int winner = arr[0];
        int wins = 0;
        
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > winner) {
                winner = arr[i];
                wins = 1;
            } else {
                wins++;
            }
            
            if (wins == k) {
                return winner;
            }
        }
        
        return winner;
    }
}