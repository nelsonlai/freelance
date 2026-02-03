/*
 * Problem: The Number of Good Subsets
 * Difficulty: Hard
 * Tags: array, dp, math, hash, bitmask
 * 
 * Approach: DP with bitmask - track products that are square-free
 * Time Complexity: O(n * 2^10) where n is length, 10 is primes <= 30
 * Space Complexity: O(2^10)
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    static constexpr int PRIMES[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    
    int getMask(int num) {
        int mask = 0;
        for (int i = 0; i < 10; i++) {
            if (num % PRIMES[i] == 0) {
                if ((num / PRIMES[i]) % PRIMES[i] == 0) {
                    return -1;
                }
                mask |= (1 << i);
            }
        }
        return mask;
    }
    
    long long pow(long long base, int exp) {
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
    int numberOfGoodSubsets(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        vector<long long> dp(1 << 10, 0);
        dp[0] = 1;
        
        for (int num = 2; num <= 30; num++) {
            if (count.find(num) == count.end()) {
                continue;
            }
            int mask = getMask(num);
            if (mask == -1) {
                continue;
            }
            
            for (int prevMask = (1 << 10) - 1; prevMask >= 0; prevMask--) {
                if ((prevMask & mask) == 0) {
                    dp[prevMask | mask] = (dp[prevMask | mask] + 
                        dp[prevMask] * count[num]) % MOD;
                }
            }
        }
        
        long long result = 0;
        for (int i = 1; i < (1 << 10); i++) {
            result = (result + dp[i]) % MOD;
        }
        
        if (count.find(1) != count.end()) {
            result = (result * pow(2, count[1])) % MOD;
        }
        
        return result;
    }
};
