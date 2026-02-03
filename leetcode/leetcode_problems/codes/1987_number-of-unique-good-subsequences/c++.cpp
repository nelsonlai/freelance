/*
 * Problem: Number of Unique Good Subsequences
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: DP - track count of subsequences ending with 0 and 1, handle leading zeros
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
public:
    int numberOfUniqueGoodSubsequences(string binary) {
        long long endsWith0 = 0;
        long long endsWith1 = 0;
        bool hasZero = false;
        
        for (char c : binary) {
            if (c == '0') {
                hasZero = true;
                endsWith0 = (endsWith0 + endsWith1) % MOD;
            } else {
                endsWith1 = (endsWith0 + endsWith1 + 1) % MOD;
            }
        }
        
        long long result = (endsWith0 + endsWith1) % MOD;
        if (hasZero) {
            result = (result + 1) % MOD;
        }
        
        return result;
    }
};