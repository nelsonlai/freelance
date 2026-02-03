/*
 * Problem: Bulb Switcher II
 * Difficulty: Medium
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int flipLights(int n, int presses) {
        if (presses == 0) {
            return 1;
        }
        if (n == 1) {
            return 2;
        }
        if (n == 2) {
            return presses == 1 ? 3 : 4;
        }
        
        if (presses == 1) {
            return 4;
        }
        if (presses == 2) {
            return 7;
        }
        
        return 8;
    }
};