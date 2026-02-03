/**
 * Problem: Maximum Points You Can Obtain from Cards
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Sliding window - find minimum subarray of length n-k, answer is total - min
 * Time Complexity: O(n) where n is length of cardPoints
 * Space Complexity: O(1)
 */

class Solution {
    public int maxScore(int[] cardPoints, int k) {
        int n = cardPoints.length;
        int windowSize = n - k;
        int total = 0;
        for (int point : cardPoints) {
            total += point;
        }
        
        int windowSum = 0;
        for (int i = 0; i < windowSize; i++) {
            windowSum += cardPoints[i];
        }
        
        int minWindow = windowSum;
        for (int i = windowSize; i < n; i++) {
            windowSum = windowSum - cardPoints[i - windowSize] + cardPoints[i];
            minWindow = Math.min(minWindow, windowSum);
        }
        
        return total - minWindow;
    }
}