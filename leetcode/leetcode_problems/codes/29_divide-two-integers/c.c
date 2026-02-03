/*
 * Problem: Divide Two Integers
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <limits.h>
#include <stdlib.h>

int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    
    int negative = (dividend < 0) != (divisor < 0);
    long long dvd = llabs((long long)dividend);
    long long dvs = llabs((long long)divisor);
    
    int quotient = 0;
    while (dvd >= dvs) {
        long long temp = dvs;
        int multiple = 1;
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        dvd -= temp;
        quotient += multiple;
    }
    
    return negative ? -quotient : quotient;
}