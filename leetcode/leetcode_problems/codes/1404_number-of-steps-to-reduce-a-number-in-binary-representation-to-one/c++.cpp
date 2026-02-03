/*
 * Problem: Number of Steps to Reduce a Number in Binary Representation to One
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: Simulate - if even divide by 2, if odd add 1, count steps
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        int carry = 0;
        
        for (int i = s.length() - 1; i > 0; i--) {
            int digit = (s[i] - '0') + carry;
            if (digit % 2 == 1) {
                steps += 2;
                carry = 1;
            } else {
                steps += 1;
                carry = 0;
            }
        }
        
        return steps + carry;
    }
};