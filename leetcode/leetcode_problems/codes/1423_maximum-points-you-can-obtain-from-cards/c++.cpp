/*
 * Problem: Maximum Points You Can Obtain from Cards
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Sliding window - find minimum subarray of length n-k, answer is total - min
 * Time Complexity: O(n) where n is length of cardPoints
 * Space Complexity: O(1)
 */

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int windowSize = n - k;
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        
        int windowSum = 0;
        for (int i = 0; i < windowSize; i++) {
            windowSum += cardPoints[i];
        }
        
        int minWindow = windowSum;
        for (int i = windowSize; i < n; i++) {
            windowSum = windowSum - cardPoints[i - windowSize] + cardPoints[i];
            minWindow = min(minWindow, windowSum);
        }
        
        return total - minWindow;
    }
};