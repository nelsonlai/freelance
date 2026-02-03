/*
 * Problem: Game of Nim
 * Difficulty: Medium
 * Tags: array, dp, math, game theory
 * 
 * Approach: Nim game - XOR of all piles, if non-zero first player wins
 * Time Complexity: O(n) where n is piles
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool nimGame(vector<int>& piles) {
        int xorSum = 0;
        for (int pile : piles) {
            xorSum ^= pile;
        }
        return xorSum != 0;
    }
};