/*
 * Problem: Nth Digit
 * Difficulty: Medium
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>

using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        int length = 1;
        long count = 9;
        int start = 1;
        
        while (n > length * count) {
            n -= length * count;
            length++;
            count *= 10;
            start *= 10;
        }
        
        start += (n - 1) / length;
        string s = to_string(start);
        return s[(n - 1) % length] - '0';
    }
};