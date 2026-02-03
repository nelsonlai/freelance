/**
 * Problem: Reveal Cards In Increasing Order
 * Difficulty: Medium
 * Tags: array, sort, queue
 * 
 * Approach: Simulate reverse process - start with sorted deck and work backwards
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for deque
 */

import java.util.*;

class Solution {
    public int[] deckRevealedIncreasing(int[] deck) {
        Arrays.sort(deck);
        int n = deck.length;
        int[] result = new int[n];
        Deque<Integer> indices = new ArrayDeque<>();
        
        for (int i = 0; i < n; i++) {
            indices.offer(i);
        }
        
        for (int card : deck) {
            int idx = indices.poll();
            result[idx] = card;
            if (!indices.isEmpty()) {
                indices.offer(indices.poll());
            }
        }
        
        return result;
    }
}