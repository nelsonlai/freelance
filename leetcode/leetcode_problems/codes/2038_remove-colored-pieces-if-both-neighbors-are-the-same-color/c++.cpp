/*
 * Problem: Remove Colored Pieces if Both Neighbors are the Same Color
 * Difficulty: Medium
 * Tags: string, greedy, math
 * 
 * Approach: Count consecutive A's and B's of length >= 3, Alice wins if more moves
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
public:
    bool winnerOfGame(string colors) {
        int aliceMoves = 0;
        int bobMoves = 0;
        
        int i = 0;
        while (i < colors.length()) {
            char ch = colors[i];
            int count = 0;
            while (i < colors.length() && colors[i] == ch) {
                count++;
                i++;
            }
            
            if (ch == 'A' && count >= 3) {
                aliceMoves += count - 2;
            } else if (ch == 'B' && count >= 3) {
                bobMoves += count - 2;
            }
        }
        
        return aliceMoves > bobMoves;
    }
};