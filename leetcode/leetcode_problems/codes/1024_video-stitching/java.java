/**
 * Problem: Video Stitching
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Greedy - sort clips, extend coverage as far as possible
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int videoStitching(int[][] clips, int time) {
        Arrays.sort(clips, (a, b) -> a[0] - b[0]);
        int result = 0;
        int end = 0;
        int i = 0;
        
        while (end < time) {
            int maxEnd = end;
            while (i < clips.length && clips[i][0] <= end) {
                maxEnd = Math.max(maxEnd, clips[i][1]);
                i++;
            }
            
            if (maxEnd == end) {
                return -1;
            }
            
            end = maxEnd;
            result++;
        }
        
        return result;
    }
}