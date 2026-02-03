/**
 * Problem: Final Value of Variable After Performing Operations
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Count increment and decrement operations
 * Time Complexity: O(n) where n is number of operations
 * Space Complexity: O(1)
 */

class Solution {
    public int finalValueAfterOperations(String[] operations) {
        int x = 0;
        for (String op : operations) {
            if (op.contains("+")) {
                x++;
            } else {
                x--;
            }
        }
        return x;
    }
}