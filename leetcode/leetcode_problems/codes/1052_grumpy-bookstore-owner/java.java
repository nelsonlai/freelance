/**
 * Problem: Grumpy Bookstore Owner
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Sliding window - find window of minutes where we can save most customers
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public int maxSatisfied(int[] customers, int[] grumpy, int minutes) {
        int baseSatisfied = 0;
        for (int i = 0; i < customers.length; i++) {
            if (grumpy[i] == 0) {
                baseSatisfied += customers[i];
            }
        }
        
        int maxExtra = 0;
        int currentExtra = 0;
        
        for (int i = 0; i < customers.length; i++) {
            if (grumpy[i] == 1) {
                currentExtra += customers[i];
            }
            if (i >= minutes && grumpy[i - minutes] == 1) {
                currentExtra -= customers[i - minutes];
            }
            maxExtra = Math.max(maxExtra, currentExtra);
        }
        
        return baseSatisfied + maxExtra;
    }
}