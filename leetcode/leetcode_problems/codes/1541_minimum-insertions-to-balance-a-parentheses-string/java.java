/**
 * Problem: Minimum Insertions to Balance a Parentheses String
 * Difficulty: Medium
 * Tags: string, greedy, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int minInsertions(String s) {
        int insertions = 0;
        int rightNeeded = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '(') {
                if (rightNeeded % 2 == 1) {
                    insertions++;
                    rightNeeded--;
                }
                rightNeeded += 2;
            } else {
                rightNeeded--;
                if (rightNeeded < 0) {
                    insertions++;
                    rightNeeded += 2;
                }
            }
        }
        
        return insertions + rightNeeded;
    }
}