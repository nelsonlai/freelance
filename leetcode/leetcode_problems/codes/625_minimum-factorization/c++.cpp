/*
 * Problem: Minimum Factorization
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: Greedy algorithm with local optimal choices
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <climits>

using namespace std;

class Solution {
public:
    int smallestFactorization(int num) {
        if (num < 2) {
            return num;
        }
        
        long long result = 0;
        long long base = 1;
        
        for (int i = 9; i >= 2; i--) {
            while (num % i == 0) {
                result += i * base;
                base *= 10;
                num /= i;
            }
        }
        
        return (num == 1 && result <= INT_MAX) ? (int)result : 0;
    }
};