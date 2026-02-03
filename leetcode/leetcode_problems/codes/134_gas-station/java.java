/**
 * Problem: Gas Station
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int totalTank = 0;
        int currentTank = 0;
        int start = 0;
        
        for (int i = 0; i < gas.length; i++) {
            totalTank += gas[i] - cost[i];
            currentTank += gas[i] - cost[i];
            
            if (currentTank < 0) {
                start = i + 1;
                currentTank = 0;
            }
        }
        
        return totalTank >= 0 ? start : -1;
    }
}