/*
 * Problem: Binary Number with Alternating Bits
 * Difficulty: Easy
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    bool hasAlternatingBits(int n) {
        int prev = n % 2;
        n /= 2;
        
        while (n > 0) {
            int curr = n % 2;
            if (curr == prev) {
                return false;
            }
            prev = curr;
            n /= 2;
        }
        
        return true;
    }
};