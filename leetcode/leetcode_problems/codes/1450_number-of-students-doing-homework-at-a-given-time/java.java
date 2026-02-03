/**
 * Problem: Number of Students Doing Homework at a Given Time
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Count students where startTime <= queryTime <= endTime
 * Time Complexity: O(n) where n is length of arrays
 * Space Complexity: O(1)
 */

class Solution {
    public int busyStudent(int[] startTime, int[] endTime, int queryTime) {
        int count = 0;
        for (int i = 0; i < startTime.length; i++) {
            if (startTime[i] <= queryTime && queryTime <= endTime[i]) {
                count++;
            }
        }
        return count;
    }
}