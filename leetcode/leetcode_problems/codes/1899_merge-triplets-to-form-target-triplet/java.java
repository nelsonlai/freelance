/**
 * Problem: Merge Triplets to Form Target Triplet
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Only use triplets where all values <= target, check if can form target
 * Time Complexity: O(n) where n is triplets
 * Space Complexity: O(1)
 */

class Solution {
    public boolean mergeTriplets(int[][] triplets, int[] target) {
        boolean[] found = new boolean[3];
        
        for (int[] triplet : triplets) {
            if (triplet[0] <= target[0] && triplet[1] <= target[1] && triplet[2] <= target[2]) {
                for (int i = 0; i < 3; i++) {
                    if (triplet[i] == target[i]) {
                        found[i] = true;
                    }
                }
            }
        }
        
        return found[0] && found[1] && found[2];
    }
}