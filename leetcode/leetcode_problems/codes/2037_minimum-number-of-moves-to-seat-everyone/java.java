/**
 * Problem: Minimum Number of Moves to Seat Everyone
 * Difficulty: Easy
 * Tags: array, greedy, sort
 * 
 * Approach: Sort both arrays, match smallest student with smallest seat
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int minMovesToSeat(int[] seats, int[] students) {
        Arrays.sort(seats);
        Arrays.sort(students);
        
        int result = 0;
        for (int i = 0; i < seats.length; i++) {
            result += Math.abs(seats[i] - students[i]);
        }
        
        return result;
    }
}