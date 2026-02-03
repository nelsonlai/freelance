/**
 * Problem: Ugly Number III
 * Difficulty: Medium
 * Tags: math, search
 * 
 * Approach: Binary search + inclusion-exclusion principle to count numbers divisible by a, b, or c
 * Time Complexity: O(log(max_val)) where max_val is the search range
 * Space Complexity: O(1)
 */
class Solution {
    private long lcm(long x, long y) {
        return x * y / gcd(x, y);
    }
    
    private long gcd(long x, long y) {
        return y == 0 ? x : gcd(y, x % y);
    }
    
    public int nthUglyNumber(int n, int a, int b, int c) {
        long ab = lcm(a, b);
        long ac = lcm(a, c);
        long bc = lcm(b, c);
        long abc = lcm(ab, c);
        
        long left = 1, right = 2_000_000_000L;
        while (left < right) {
            long mid = (left + right) / 2;
            long count = mid / a + mid / b + mid / c 
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
}