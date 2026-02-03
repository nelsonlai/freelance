/*
 * Problem: Three Divisors
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Check if n is a perfect square of a prime number
 * Time Complexity: O(sqrt(n))
 * Space Complexity: O(1)
 */

#include <cmath>

class Solution {
private:
    bool isPrime(int num) {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
    
public:
    bool isThree(int n) {
        int sqrtN = sqrt(n);
        return sqrtN * sqrtN == n && isPrime(sqrtN);
    }
};