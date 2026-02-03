/*
 * Problem: Valid Perfect Square
 * Difficulty: Easy
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 2) {
            return true;
        }
        
        long left = 2, right = num / 2;
        while (left <= right) {
            long mid = (left + right) / 2;
            long square = mid * mid;
            if (square == num) {
                return true;
            } else if (square < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
};