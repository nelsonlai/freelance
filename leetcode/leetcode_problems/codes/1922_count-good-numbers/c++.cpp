/*
 * Problem: Count Good Numbers
 * Difficulty: Medium
 * Tags: string, math, fast exponentiation
 * 
 * Approach: Even positions: 5 choices (0,2,4,6,8), odd positions: 4 choices (2,3,5,7)
 * Time Complexity: O(log n) for exponentiation
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
private:
    const int MOD = 1000000007;
    
    long long power(long long base, long long exp) {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return result;
    }
    
public:
    int countGoodNumbers(long long n) {
        long long evenCount = (n + 1) / 2;
        long long oddCount = n / 2;
        
        return (power(5, evenCount) * power(4, oddCount)) % MOD;
    }
};