/*
 * Problem: Minimum Non-Zero Product of the Array Elements
 * Difficulty: Medium
 * Tags: array, greedy, math, fast exponentiation
 * 
 * Approach: Minimize product by pairing (2^p-2) with 1, leaving (2^p-1) alone
 * Time Complexity: O(p) for exponentiation
 * Space Complexity: O(1)
 */

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
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
    int minNonZeroProduct(int p) {
        long long maxNum = (1LL << p) - 1;  // 2^p - 1
        long long pairs = (maxNum - 1) / 2;
        
        // (maxNum - 1) ^ pairs mod MOD
        long long base = (maxNum - 1) % MOD;
        long long result = power(base, pairs);
        result = (result * (maxNum % MOD)) % MOD;
        
        return result;
    }
};