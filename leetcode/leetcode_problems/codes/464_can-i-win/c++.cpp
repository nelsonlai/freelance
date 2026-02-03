/*
 * Problem: Can I Win
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_map>

using namespace std;

class Solution {
private:
    bool canWin(int used, int remaining, int maxChoosable, unordered_map<int, bool>& memo) {
        if (memo.find(used) != memo.end()) {
            return memo[used];
        }
        
        for (int i = 1; i <= maxChoosable; i++) {
            if (!(used & (1 << i))) {
                if (i >= remaining || !canWin(used | (1 << i), remaining - i, maxChoosable, memo)) {
                    memo[used] = true;
                    return true;
                }
            }
        }
        
        memo[used] = false;
        return false;
    }

public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (desiredTotal <= maxChoosableInteger) {
            return true;
        }
        if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
            return false;
        }
        
        unordered_map<int, bool> memo;
        return canWin(0, desiredTotal, maxChoosableInteger, memo);
    }
};