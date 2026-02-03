/**
 * Problem: Min Max Game
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int minMaxGame(int[] nums) {
        List<Integer> list = new ArrayList<>();
        for (int num : nums) {
            list.add(num);
        }
        
        while (list.size() > 1) {
            List<Integer> newList = new ArrayList<>();
            for (int i = 0; i < list.size() / 2; i++) {
                if (i % 2 == 0) {
                    newList.add(Math.min(list.get(2 * i), list.get(2 * i + 1)));
                } else {
                    newList.add(Math.max(list.get(2 * i), list.get(2 * i + 1)));
                }
            }
            list = newList;
        }
        
        return list.get(0);
    }
}