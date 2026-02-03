/*
 * Problem: Count Odd Numbers in an Interval Range
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int countOdds(int low, int high) {
        return (high - low + 1 + (low % 2)) / 2;
    }
};