/*
 * Problem: Matchsticks to Square
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    bool backtrack(int index, vector<int>& matchsticks, vector<int>& sides, int side) {
        if (index == matchsticks.size()) {
            return sides[0] == side && sides[1] == side && sides[2] == side && sides[3] == side;
        }
        
        for (int i = 0; i < 4; i++) {
            if (sides[i] + matchsticks[index] <= side) {
                sides[i] += matchsticks[index];
                if (backtrack(index + 1, matchsticks, sides, side)) {
                    return true;
                }
                sides[i] -= matchsticks[index];
                if (sides[i] == 0) {
                    break;
                }
            }
        }
        
        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        int total = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (total % 4 != 0) {
            return false;
        }
        
        int side = total / 4;
        sort(matchsticks.rbegin(), matchsticks.rend());
        vector<int> sides(4, 0);
        
        return backtrack(0, matchsticks, sides, side);
    }
};