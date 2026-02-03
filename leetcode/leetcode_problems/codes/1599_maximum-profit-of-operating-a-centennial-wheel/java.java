/**
 * Problem: Maximum Profit of Operating a Centennial Wheel
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int minOperationsMaxProfit(int[] customers, int boardingCost, int runningCost) {
        int waiting = 0;
        int profit = 0;
        int maxProfit = 0;
        int result = -1;
        int i = 0;
        
        while (waiting > 0 || i < customers.length) {
            if (i < customers.length) {
                waiting += customers[i];
            }
            
            int board = Math.min(4, waiting);
            waiting -= board;
            profit += board * boardingCost - runningCost;
            
            if (profit > maxProfit) {
                maxProfit = profit;
                result = i + 1;
            }
            
            i++;
        }
        
        return result;
    }
}