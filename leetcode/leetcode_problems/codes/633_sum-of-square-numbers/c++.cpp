/*
 * Problem: Sum of Square Numbers
 * Difficulty: Medium
 * Tags: array, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <cmath>

using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        long left = 0;
        long right = (long)sqrt(c);
        
        while (left <= right) {
            long sum = left * left + right * right;
            if (sum == c) {
                return true;
            } else if (sum < c) {
                left++;
            } else {
                right--;
            }
        }
        
        return false;
    }
};