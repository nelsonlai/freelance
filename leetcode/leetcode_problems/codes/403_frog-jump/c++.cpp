/*
 * Problem: Frog Jump
 * Difficulty: Hard
 * Tags: array, dp, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
private:
    bool dfs(int position, int lastJump, int target, unordered_set<int>& stoneSet, unordered_map<string, bool>& memo) {
        if (position == target) {
            return true;
        }
        
        string key = to_string(position) + "," + to_string(lastJump);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        for (int jump = lastJump - 1; jump <= lastJump + 1; jump++) {
            if (jump > 0) {
                int nextPosition = position + jump;
                if (stoneSet.find(nextPosition) != stoneSet.end() && 
                    dfs(nextPosition, jump, target, stoneSet, memo)) {
                    memo[key] = true;
                    return true;
                }
            }
        }
        
        memo[key] = false;
        return false;
    }

public:
    bool canCross(vector<int>& stones) {
        unordered_set<int> stoneSet(stones.begin(), stones.end());
        unordered_map<string, bool> memo;
        
        if (stones[1] != 1) {
            return false;
        }
        
        return dfs(1, 1, stones.back(), stoneSet, memo);
    }
};