/**
 * Problem: Super Washing Machines
 * Difficulty: Hard
 * Tags: array, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int findMinMoves(int[] machines) {
        int total = 0;
        int n = machines.length;
        for (int load : machines) {
            total += load;
        }
        
        if (total % n != 0) {
            return -1;
        }
        
        int target = total / n;
        int result = 0;
        int balance = 0;
        
        for (int load : machines) {
            balance += load - target;
            result = Math.max(result, Math.max(Math.abs(balance), load - target));
        }
        
        return result;
    }
}