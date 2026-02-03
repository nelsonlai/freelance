/*
 * Problem: Elimination Game
 * Difficulty: Medium
 * Tags: math, sort
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int lastRemaining(int n) {
        bool left = true;
        int remaining = n;
        int step = 1;
        int head = 1;
        
        while (remaining > 1) {
            if (left || remaining % 2 == 1) {
                head += step;
            }
            remaining /= 2;
            step *= 2;
            left = !left;
        }
        
        return head;
    }
};