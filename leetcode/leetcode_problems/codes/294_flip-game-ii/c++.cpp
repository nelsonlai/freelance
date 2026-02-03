/*
 * Problem: Flip Game II
 * Difficulty: Medium
 * Tags: string, dp, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<string, bool> memo;
    
public:
    bool canWin(string currentState) {
        if (memo.find(currentState) != memo.end()) {
            return memo[currentState];
        }
        
        for (int i = 0; i < (int)currentState.length() - 1; i++) {
            if (currentState[i] == '+' && currentState[i + 1] == '+') {
                string newState = currentState.substr(0, i) + "--" + currentState.substr(i + 2);
                if (!canWin(newState)) {
                    memo[currentState] = true;
                    return true;
                }
            }
        }
        
        memo[currentState] = false;
        return false;
    }
};