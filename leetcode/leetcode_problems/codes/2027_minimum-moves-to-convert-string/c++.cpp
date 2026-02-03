/*
 * Problem: Minimum Moves to Convert String
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Greedy - convert leftmost 'X' and next 2 characters in each move
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
public:
    int minimumMoves(string s) {
        int moves = 0;
        int i = 0;
        
        while (i < s.length()) {
            if (s[i] == 'X') {
                moves++;
                i += 3; // Skip next 2 characters
            } else {
                i++;
            }
        }
        
        return moves;
    }
};