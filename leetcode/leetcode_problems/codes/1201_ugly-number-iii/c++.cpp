/*
 * Problem: Ugly Number III
 * Difficulty: Medium
 * Tags: math, search
 * 
 * Approach: Binary search + inclusion-exclusion principle to count numbers divisible by a, b, or c
 * Time Complexity: O(log(max_val)) where max_val is the search range
 * Space Complexity: O(1)
 */
#include <algorithm>

using namespace std;

class Solution {
public:
    long long lcm(long long x, long long y) {
        return x * y / __gcd(x, y);
    }
    
    int nthUglyNumber(int n, int a, int b, int c) {
        long long ab = lcm(a, b);
        long long ac = lcm(a, c);
        long long bc = lcm(b, c);
        long long abc = lcm(ab, c);
        
        long long left = 1, right = 2000000000LL;
        while (left < right) {
            long long mid = (left + right) / 2;
            long long count = mid / a + mid / b + mid / c 
                            - mid / ab - mid / ac - mid / bc 
                            + mid / abc;
            if (count < n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return (int) left;
    }
};