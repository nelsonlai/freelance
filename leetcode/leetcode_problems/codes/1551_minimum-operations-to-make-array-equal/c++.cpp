/*
 * Problem: Minimum Operations to Make Array Equal
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int minOperations(int n) {
        if (n % 2 == 1) {
            return (n / 2) * (n / 2 + 1);
        } else {
            return (n / 2) * (n / 2);
        }
    }
};