/**
 * Problem: Matchsticks to Square
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public boolean makesquare(int[] matchsticks) {
        int total = Arrays.stream(matchsticks).sum();
        if (total % 4 != 0) {
            return false;
        }
        
        int side = total / 4;
        Arrays.sort(matchsticks);
        reverse(matchsticks);
        int[] sides = new int[4];
        
        return backtrack(0, matchsticks, sides, side);
    }
    
    private boolean backtrack(int index, int[] matchsticks, int[] sides, int side) {
        if (index == matchsticks.length) {
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
    
    private void reverse(int[] arr) {
        int left = 0, right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}