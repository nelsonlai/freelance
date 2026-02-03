/*
 * Problem: Perfect Number
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num <= 1) {
            return false;
        }
        
        int total = 1;
        int i = 2;
        while (i * i <= num) {
            if (num % i == 0) {
                total += i;
                if (i * i != num) {
                    total += num / i;
                }
            }
            i++;
        }
        
        return total == num;
    }
};