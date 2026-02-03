/**
 * Problem: Maximum Number of People That Can Be Caught in Tag
 * Difficulty: Medium
 * Tags: array, greedy, two pointers
 * 
 * Approach: Two pointers - match taggers (1) with runners (0) within distance
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int catchMaximumAmountofPeople(int[] team, int dist) {
        List<Integer> taggers = new ArrayList<>();
        List<Integer> runners = new ArrayList<>();
        
        for (int i = 0; i < team.length; i++) {
            if (team[i] == 1) {
                taggers.add(i);
            } else {
                runners.add(i);
            }
        }
        
        if (taggers.isEmpty() || runners.isEmpty()) {
            return 0;
        }
        
        int count = 0;
        int tIdx = 0, rIdx = 0;
        
        while (tIdx < taggers.size() && rIdx < runners.size()) {
            if (Math.abs(taggers.get(tIdx) - runners.get(rIdx)) <= dist) {
                count++;
                tIdx++;
                rIdx++;
            } else if (taggers.get(tIdx) < runners.get(rIdx)) {
                tIdx++;
            } else {
                rIdx++;
            }
        }
        
        return count;
    }
}