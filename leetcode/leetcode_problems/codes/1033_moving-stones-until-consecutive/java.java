/**
 * Problem: Moving Stones Until Consecutive
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Sort stones, calculate min and max moves
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int[] numMovesStones(int a, int b, int c) {
        int[] stones = {a, b, c};
        Arrays.sort(stones);
        int x = stones[0], y = stones[1], z = stones[2];
        
        int maxMoves = (z - x - 2);
        
        int minMoves;
        if (z - x == 2) {
            minMoves = 0;
        } else if (y - x <= 2 || z - y <= 2) {
            minMoves = 1;
        } else {
            minMoves = 2;
        }
        
        return new int[]{minMoves, maxMoves};
    }
}