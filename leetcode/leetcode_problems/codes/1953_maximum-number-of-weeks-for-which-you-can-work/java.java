/**
 * Problem: Maximum Number of Weeks for Which You Can Work
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: If max project <= sum of others + 1, can complete all; otherwise limited by max
 * Time Complexity: O(n) where n is milestones
 * Space Complexity: O(1)
 */

class Solution {
    public long numberOfWeeks(int[] milestones) {
        long total = 0;
        int maxMilestone = 0;
        for (int m : milestones) {
            total += m;
            maxMilestone = Math.max(maxMilestone, m);
        }
        long rest = total - maxMilestone;
        
        if (maxMilestone <= rest + 1) {
            return total;
        } else {
            return 2 * rest + 1;
        }
    }
}