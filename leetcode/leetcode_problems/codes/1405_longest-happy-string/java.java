/**
 * Problem: Longest Happy String
 * Difficulty: Medium
 * Tags: string, tree, greedy, queue, heap
 * 
 * Approach: Greedy - use heap to always pick most frequent char (if can't use same twice)
 * Time Complexity: O(n log 3) where n is total characters
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public String longestDiverseString(int a, int b, int c) {
        PriorityQueue<int[]> heap = new PriorityQueue<>((x, y) -> y[0] - x[0]);
        if (a > 0) heap.offer(new int[]{a, 0});
        if (b > 0) heap.offer(new int[]{b, 1});
        if (c > 0) heap.offer(new int[]{c, 2});
        
        StringBuilder result = new StringBuilder();
        char[] chars = {'a', 'b', 'c'};
        
        while (!heap.isEmpty()) {
            int[] first = heap.poll();
            int count1 = first[0];
            char char1 = chars[first[1]];
            
            if (result.length() >= 2 && result.charAt(result.length() - 1) == char1 && 
                result.charAt(result.length() - 2) == char1) {
                if (heap.isEmpty()) {
                    break;
                }
                int[] second = heap.poll();
                int count2 = second[0];
                char char2 = chars[second[1]];
                result.append(char2);
                count2--;
                if (count2 > 0) {
                    heap.offer(new int[]{count2, second[1]});
                }
                heap.offer(first);
            } else {
                result.append(char1);
                count1--;
                if (count1 > 0) {
                    heap.offer(new int[]{count1, first[1]});
                }
            }
        }
        
        return result.toString();
    }
}