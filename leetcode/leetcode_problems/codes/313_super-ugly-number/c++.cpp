/*
 * Problem: Super Ugly Number
 * Difficulty: Medium
 * Tags: array, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> ugly(n);
        vector<int> indices(primes.size(), 0);
        ugly[0] = 1;
        
        for (int i = 1; i < n; i++) {
            int nextUgly = INT_MAX;
            for (int j = 0; j < primes.size(); j++) {
                nextUgly = min(nextUgly, ugly[indices[j]] * primes[j]);
            }
            ugly[i] = nextUgly;
            
            for (int j = 0; j < primes.size(); j++) {
                if (ugly[indices[j]] * primes[j] == nextUgly) {
                    indices[j]++;
                }
            }
        }
        
        return ugly[n - 1];
    }
};