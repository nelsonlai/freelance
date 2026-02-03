/*
 * Problem: Number of Ways to Paint N × 3 Grid
 * Difficulty: Hard
 * Tags: dp
 * 
 * Approach: DP - track patterns (ABA vs ABC), count valid transitions
 * Time Complexity: O(n) where n is number of rows
 * Space Complexity: O(1) using rolling variables
 */

class Solution {
public:
    int numOfWays(int n) {
        int MOD = 1000000007;
        long long aba = 6;  // ABA pattern
        long long abc = 6;  // ABC pattern
        
        for (int i = 1; i < n; i++) {
            long long newAba = (aba * 3 + abc * 2) % MOD;
            long long newAbc = (aba * 2 + abc * 2) % MOD;
            aba = newAba;
            abc = newAbc;
        }
        
        return (aba + abc) % MOD;
    }
};